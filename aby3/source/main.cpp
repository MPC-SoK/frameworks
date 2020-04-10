#include "mult3.h"
#include "innerprod.h"
#include "xtabs.h"

// testing and command line parsing
#include <tests_cryptoTools/UnitTests.h>
#include <cryptoTools/Common/CLP.h>
std::vector<std::string> unitTestTag{ "u", "unitTest" };


void help()
{
	std::cout << "-u                  ~~ to run all tests" << std::endl;
	std::cout << "-u n1 [n2 ...]      ~~ to run test n1, n2, ..." << std::endl;
	std::cout << "-u -list            ~~ to list all tests" << std::endl;
}

int main(int argc, char** argv)
{
	try {

		oc::CLP cmd(argc, argv);

        // this assigns the appropriate test function to each command-line arg
        // functions are defined in their respective .h files
		if (cmd.isSet(unitTestTag))
		{
            oc::TestCollection sample_tests([](oc::TestCollection& tc) {
                tc.add("mult3    ", mult3_test);
                tc.add("innerprod", innerprod_test);
                tc.add("xtabs    ", xtabs_test);
            });

			sample_tests.runIf(cmd);
			return 0;
		}

        help();

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
