#include "mult3.h"
#include "innerprod.h"
#include "xtabs.h"

// testing and command line parsing
#include <tests_cryptoTools/UnitTests.h>
#include <cryptoTools/Common/CLP.h>
std::vector<std::string> unitTestTag{"u", "unitTest"};
std::vector<std::string> playerTag{"p", "player"};

// convenience function
#include <cryptoTools/Network/IOService.h>
#include "aby3/sh3/Sh3Runtime.h"
#include "aby3/sh3/Sh3Encryptor.h"
#include "aby3/sh3/Sh3Evaluator.h"

// This function sets up the basic classes that we will
// use to perform some computation. This mostly consists
// of creating Channels (network sockets) to the other
// parties and then establishing some shared randomness.
void setup_samples(
	aby3::u64 partyIdx,
	oc::IOService &ios,
	aby3::Sh3Encryptor &enc,
	aby3::Sh3Evaluator &eval,
	aby3::Sh3Runtime &runtime);

void help()
{
	std::cout << "-u                  ~~ to run all tests" << std::endl;
	std::cout << "-u n1 [n2 ...]      ~~ to run test n1, n2, ..." << std::endl;
	std::cout << "-u -list            ~~ to list all tests" << std::endl;

	std::cout << "-p party 		  ~~ indicate which party you are" << std::endl;
}

int main(int argc, char **argv)
{
	try
	{

		oc::CLP cmd(argc, argv);

		oc::u64 player;
		if (cmd.isSet(playerTag))
		{
			player = cmd.getOr(playerTag, -1);
		}
		else
		{
			std::cout << "You need to specify which party you are" << std::endl;
			return 0;
		}

		// this calls the appropriate test function based on command-line arg
		// functions are defined in their respective .h files
		if (cmd.isSet(unitTestTag))
		{
			std::string none = "";
			if (cmd.getOr(unitTestTag, none).compare("mult3") == 0)
			{
				// hardcoded input value. expected result: 3*4*5 = 60
				int value = 3 + player;
				mult3_test(player, value);
			}
			if (cmd.getOr(unitTestTag, none).compare("innerprod") == 0)
			{
				std::vector<int> values(10);
				// expected result: (0*0) + (1*2) + (2*4) + ... = 570
				for (uint i = 0; i < values.size(); i++)
				{
					values[i] = (player + 1) * i;
				}
				innerprod_test(player, values);
			}
			if (cmd.getOr(unitTestTag, none).compare("xtabs") == 0)
			{
				std::vector<int> ids{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
				std::vector<int> values{0, 2, 2, 3, 4, 5, 6, 7, 8, 9};
				xtabs_test(player, ids, values, 10);
			}

			return 0;
		}

		help();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

using namespace aby3;
using namespace oc;
using namespace aby3;
using namespace oc;
void setup_samples(
	aby3::u64 partyIdx,
	oc::IOService &ios,
	aby3::Sh3Encryptor &enc,
	aby3::Sh3Evaluator &eval,
	aby3::Sh3Runtime &runtime)
{
	// A CommPkg is a pair of Channels (network sockets) to the other parties.
	// See cryptoTools\frontend_cryptoTools\Tutorials\Network.cpp
	// for details.
	// since we're running them all locally, they're sitting on 3 different ports.
	aby3::CommPkg comm;
	switch (partyIdx)
	{
	case 0:
		comm.mNext = oc::Session(ios, "127.0.0.1:1313", oc::SessionMode::Server, "01").addChannel();
		comm.mPrev = oc::Session(ios, "127.0.0.1:1314", oc::SessionMode::Server, "02").addChannel();
		break;
	case 1:
		comm.mNext = oc::Session(ios, "127.0.0.1:1315", oc::SessionMode::Server, "12").addChannel();
		comm.mPrev = oc::Session(ios, "127.0.0.1:1313", oc::SessionMode::Client, "01").addChannel();
		break;
	default:
		comm.mNext = oc::Session(ios, "127.0.0.1:1314", oc::SessionMode::Client, "02").addChannel();
		comm.mPrev = oc::Session(ios, "127.0.0.1:1315", oc::SessionMode::Client, "12").addChannel();
		break;
	}

	// in a real work example, where parties
	// have different IPs, you have to give the
	// Clients the IP of the server and you give
	// the servers their own IP (to listen to).

	// Establishes some shared randomness needed for the later protocols
	enc.init(partyIdx, comm, sysRandomSeed());

	// Establishes some shared randomness needed for the later protocols
	eval.init(partyIdx, comm, sysRandomSeed());

	// Copies the Channels and will use them for later protcols.
	runtime.init(partyIdx, comm);
}
