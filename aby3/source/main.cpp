#include "mult3.h"
#include "innerprod.h"
#include "xtabs.h"

// testing and command line parsing
#include <tests_cryptoTools/UnitTests.h>
#include <cryptoTools/Common/CLP.h>
std::vector<std::string> unitTestTag{ "u", "unitTest" };
std::vector<std::string> playerTag{ "p", "player" };


void help()
{
	std::cout << "-u                  ~~ to run all tests" << std::endl;
	std::cout << "-u n1 [n2 ...]      ~~ to run test n1, n2, ..." << std::endl;
	std::cout << "-u -list            ~~ to list all tests" << std::endl;

	std::cout << "-p party 		  ~~ indicate which party you are" << std::endl;
}

int main(int argc, char** argv)
{
	try {

		oc::CLP cmd(argc, argv);

		oc::u64 player;
		if (cmd.isSet(playerTag)) {
			player = cmd.getOr(playerTag, -1);
		} else {
			std::cout << "You need to specify which player you are" << std::endl;
			return 0;
		}

        	// this calls the appropriate test function based on command-line arg
        	// functions are defined in their respective .h files
		if (cmd.isSet(unitTestTag))
		{
			std::string none = "";
			if (cmd.getOr(unitTestTag, none).compare("mult3") == 0) {
				// hardcodes input value
				int value = 3 + player; 
				mult3_test(player, value);
			}
			if (cmd.getOr(unitTestTag, none).compare("innerprod") == 0) {
				//innerprod_test(player);
				innerprod_test();
			}
			if (cmd.getOr(unitTestTag, none).compare("xtabs") == 0) {
				//xtabs_test(player);
				xtabs_test();
			}

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
