/*
 * Sharemind MPC example programs
 * Copyright (C) 2018 Sharemind
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **/


#include <boost/program_options.hpp>
#include <iostream>
#include <LogHard/Backend.h>
#include <LogHard/FileAppender.h>
#include <LogHard/Logger.h>
#include <LogHard/StdAppender.h>
#include <memory>
#include <sharemind/controller/SystemController.h>
#include <sharemind/controller/SystemControllerConfiguration.h>
#include <sharemind/controller/SystemControllerGlobals.h>
#include <sharemind/DebugOnly.h>
#include <sharemind/GlobalDeleter.h>
#include <sharemind/MakeUnique.h>
#include <sstream>
#include <string>

namespace sm = sharemind;

inline std::shared_ptr<void> newGlobalBuffer(std::size_t const size) {
    auto * const b = size ? ::operator new(size) : nullptr;
    try {
        return std::shared_ptr<void>(b, sm::GlobalDeleter());
    } catch (...) {
        ::operator delete(b);
        throw;
    }
}

inline std::shared_ptr<void> newGlobalBuffer(void const * const data,
                                             std::size_t const size)
{
    auto r(newGlobalBuffer(size));
    std::memcpy(r.get(), data, size);
    return r;
}

struct ExtraIndentExceptionFormatter {

    template <typename OutStream>
    void operator()(std::size_t const exceptionNumber,
                    std::size_t const totalExceptions,
                    std::exception_ptr e,
                    OutStream out) noexcept
    {
        assert(e);
        out << "    ";
        return LogHard::Logger::StandardFormatter()(
                    exceptionNumber,
                    totalExceptions,
                    std::move(e),
                    std::forward<OutStream>(out));
    }

};

int main(int argc, char ** argv) {
    std::unique_ptr<sm::SystemControllerConfiguration> config;

    try {
        namespace po = boost::program_options;

        po::options_description desc(
            "ScalarProduct\n"
            "Usage: ScalarProduct [OPTION]...\n\n"
            "Options");
        desc.add_options()
            ("conf,c", po::value<std::string>(),
                "Set the configuration file.")
            ("help", "Print this help");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return EXIT_SUCCESS;
        }
        if (vm.count("conf")) {
            config = sm::makeUnique<sm::SystemControllerConfiguration>(
                         vm["conf"].as<std::string>());
        } else {
            config = sm::makeUnique<sm::SystemControllerConfiguration>();
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    auto logBackend(std::make_shared<LogHard::Backend>());
    logBackend->addAppender(std::make_shared<LogHard::StdAppender>());
    logBackend->addAppender(
                std::make_shared<LogHard::FileAppender>(
                    "ScalarProduct.log",
                    LogHard::FileAppender::OVERWRITE));
    const LogHard::Logger logger(logBackend);

    logger.info() << "This is a stand alone Sharemind application demo";
    logger.info() << "It privately computes the scalar product of the following two vectors";

    // Generate some user for input
    std::vector<sm::Int64> a;
    std::vector<sm::Int64> b;

    for (sm::Int64 i = -5; i < 5; ++i) {
        a.push_back(i+2);
    }
    for (sm::Int64 i = 0; i < 10; ++i) {
        b.push_back(i);
    }

    assert(a.size() == b.size());

    {
        std::ostringstream oss;
        oss << "Vector A: [ ";
        for (const auto val : a) {
            oss << val << ' ';
        }
        oss << ']';
        logger.info() << oss.str();
    }

    {
        std::ostringstream oss;
        oss << "Vector B: [ ";
        for (const auto val : b) {
            oss << val << ' ';
        }
        oss << ']';
        logger.info() << oss.str();
    }

    try {
        sm::SystemControllerGlobals systemControllerGlobals;
        sm::SystemController c(logger, *config);

        // Initialize the argument map and set the arguments
        sm::IController::ValueMap arguments;
        arguments["a"] =
                std::make_shared<sm::IController::Value>(
                    "pd_shared3p",
                    "int64",
                    newGlobalBuffer(a.data(), sizeof(sm::Int64) * a.size()),
                    sizeof(sm::Int64) * a.size());
        arguments["b"] =
                std::make_shared<sm::IController::Value>(
                    "pd_shared3p",
                    "int64",
                    newGlobalBuffer(b.data(), sizeof(sm::Int64) * b.size()),
                    sizeof(sm::Int64) * b.size());

        // Run code
        logger.info() << "Sending secret shared arguments and running SecreC bytecode on the servers";
        sm::IController::ValueMap results = c.runCode("scalar_product.sb", arguments);

        // Print the result
        sm::IController::ValueMap::const_iterator it = results.find("c");
    if (it == results.end()) {
            logger.error() << "Missing 'c' result value.";
            return EXIT_FAILURE;
	}

	try {
            sm::Int64 c = it->second->getValue<sm::Int64>();
            logger.info() << "The computed scalar product is: " << c;
        } catch (const sm::IController::Value::ParseException & e) {
            logger.error() << "Failed to cast 'c' to appropriate type: " <<
                e.what();
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    } catch (const sm::IController::WorkerException & e) {
        logger.fatal() << "Multiple exceptions caught:";
        for (size_t i = 0u; i < e.numWorkers(); i++) {
            if (std::exception_ptr ep = e.nested_ptrs()[i]) {
                logger.fatal() << "  Exception from server " << i << ':';
                try {
                    std::rethrow_exception(std::move(ep));
                } catch (...) {
                    logger.printCurrentException<LogHard::Priority::Fatal>(
                                ExtraIndentExceptionFormatter());
                }
            }
        }
    } catch (const std::exception & e) {
        logger.error() << "Caught exception: " << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
