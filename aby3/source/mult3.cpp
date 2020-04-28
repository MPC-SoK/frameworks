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
	setup_samples(partyIdx, ios, enc, eval, runtime);

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
