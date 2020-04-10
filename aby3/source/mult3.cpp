#include <iostream>
#include <cryptoTools/Network/IOService.h>

#include "aby3/sh3/Sh3Runtime.h"
#include "aby3/sh3/Sh3Encryptor.h"
#include "aby3/sh3/Sh3Evaluator.h"

#include "mult3.h"

using namespace oc;
using namespace aby3;
/*
 * mult3 
 * 
 * multiplies three numbers together
 * lots of this code is ported from Peter Rindal's aby3Tutorial.cpp
 *
 */

// This function sets up the basic classes that we will 
// use to perform some computation. This mostly consists
// of creating Channels (network sockets) to the other 
// parties and then establishing some shared randomness.
void setup(
	u64 partyIdx,
	IOService& ios,
	Sh3Encryptor& enc,
	Sh3Evaluator& eval,
	Sh3Runtime& runtime)
{
	// A CommPkg is a pair of Channels (network sockets) to the other parties.
	// See cryptoTools\frontend_cryptoTools\Tutorials\Network.cpp 
	// for details.
	// since we're running them all locally, they're sitting on 3 different ports.
	CommPkg comm;
	switch (partyIdx)
	{
	case 0:
		comm.mNext = Session(ios, "127.0.0.1:1313", SessionMode::Server, "01").addChannel();
		comm.mPrev = Session(ios, "127.0.0.1:1314", SessionMode::Server, "02").addChannel();
		break;
	case 1:
		comm.mNext = Session(ios, "127.0.0.1:1315", SessionMode::Server, "12").addChannel();
		comm.mPrev = Session(ios, "127.0.0.1:1313", SessionMode::Client, "01").addChannel();
		break;
	default:
		comm.mNext = Session(ios, "127.0.0.1:1314", SessionMode::Client, "02").addChannel();
		comm.mPrev = Session(ios, "127.0.0.1:1315", SessionMode::Client, "12").addChannel();
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
void mult3_test(u64 partyIdx, int value){
	if (partyIdx == 0) 
		std::cout << "testing mult3..." << std::endl;
	
	IOService ios;

	// Sh3Encryptor allows us to generate and reconstruct secret shared values. 
	Sh3Encryptor enc;
	// Sh3Evaluator will allow us to perform some of the 
	// most common interactive protocols, e.g. multiplication.
	Sh3Evaluator eval;
	// Sh3Runtime does networking and helps schedule operations in parallel 
	Sh3Runtime runtime;
	setup(partyIdx, ios, enc, eval, runtime);

	std::vector<si64> sharedVec(3);

	/* Convert clear values from each player to secure types.
	 * tutorial suggests doing this asynchronously by task &='ing each call
	 * instead of calling .get() immediately
	 * This didn't compile for me; the runtime destructor was getting called way too early.
	 */
	for (u64 i = 0; i < sharedVec.size(); ++i) {
		if (i % 3 == partyIdx)
			enc.localInt(runtime, value, sharedVec[i]).get();
		else
			enc.remoteInt(runtime, sharedVec[i]).get();
	}
	
	/* multiply them together */
	si64 prod = sharedVec[0];
	Sh3Task task = runtime.noDependencies();
	for (u64 i = 1; i < sharedVec.size(); ++i)
		task = eval.asyncMul(task, prod, sharedVec[i], prod);

	task.get();
	
	/* reveal result */
	i64 result;
	enc.revealAll(runtime, prod, result).get();
	std::cout << "product: " << result << std::endl;
}
