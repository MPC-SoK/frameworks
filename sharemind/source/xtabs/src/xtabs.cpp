/*
 * Sharemind MPC example programs
 * Copyright (C) 2018 Marcella Hastings
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
            "Crosstabs\n"
            "Usage: Crosstabs [OPTION]...\n\n"
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
                    "Crosstabs.log",
                    LogHard::FileAppender::OVERWRITE));
    const LogHard::Logger logger(logBackend);

    logger.info() << "This is a stand alone Sharemind application demo";
    logger.info() << "It privately computes the crosstabulation of two data sets";

    // Generate some user for input
    std::vector<sm::Int64> xids;
    std::vector<sm::Int64> xbins;
    std::vector<sm::Int64> yids;
    std::vector<sm::Int64> yvals;

    for(int i=0; i<10; i++) {
        xids.push_back(i);
        xbins.push_back(std::rand() % 5);
        std::cout << xids[i] << "\t" << xbins[i] << std::endl;

        yids.push_back(i);
        yvals.push_back(std::rand() % 100);
        std::cout << yids[i] << "\t" << yvals[i] << std::endl;
    }

    try {
        sm::SystemControllerGlobals systemControllerGlobals;
        sm::SystemController c(logger, *config);

        // Initialize the argument map and set the arguments
        sm::IController::ValueMap arguments;

        arguments["xids"] = 
            std::make_shared<sm::IController::Value>(
                "pd_shared3p",
                "int64",
                newGlobalBuffer(xids.data(),sizeof(sm::Int64) * xids.size()),
                sizeof(sm::Int64) * xids.size());
        
        arguments["xbins"] = 
            std::make_shared<sm::IController::Value>(
                "pd_shared3p",
                "int64",
                newGlobalBuffer(xbins.data(),sizeof(sm::Int64) * xbins.size()),
                sizeof(sm::Int64) * xbins.size());
        
        arguments["yids"] = 
            std::make_shared<sm::IController::Value>(
                "pd_shared3p",
                "int64",
                newGlobalBuffer(yids.data(),sizeof(sm::Int64) * yids.size()),
                sizeof(sm::Int64) * yids.size());
        
        arguments["yvals"] = 
            std::make_shared<sm::IController::Value>(
                "pd_shared3p",
                "int64",
                newGlobalBuffer(yvals.data(),sizeof(sm::Int64) * yvals.size()),
                sizeof(sm::Int64) * yvals.size());
	
	// Run code
        logger.info() << "Sending secret shared arguments and running SecreC bytecode on the servers";
        sm::IController::ValueMap results = c.runCode("xtabs.sb", arguments);

        // Print the result
        sm::IController::ValueMap::const_iterator it = results.find("binsums");
    if (it == results.end()) {
            logger.error() << "Missing 'binsums' result value.";
            return EXIT_FAILURE;
	}

	try {
            std::vector<sm::Int64> binsums = it->second->getVector<sm::Int64>();;
            logger.info() << "The computed bin sums are: ";
            for (int i=0; i < 5; i++) {
              logger.info() << i << "\t" << binsums[i];
            }
        } catch (const sm::IController::Value::ParseException & e) {
            logger.error() << "Failed to cast output to appropriate type: " <<
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
