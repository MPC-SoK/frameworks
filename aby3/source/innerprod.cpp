#include <iostream>
#include <cryptoTools/Network/IOService.h>

#include "aby3/sh3/Sh3Runtime.h"
#include "aby3/sh3/Sh3Encryptor.h"
#include "aby3/sh3/Sh3Evaluator.h"

#include "innerprod.h"

using namespace oc;
using namespace aby3;

void innerprod_test(oc::u64 partyIdx, std::vector<int> values)
{
	if (partyIdx == 0)
		std::cout << "testing innerprod..." << std::endl;

	IOService ios;
	Sh3Encryptor enc;
	Sh3Evaluator eval;
	Sh3Runtime runtime;
	setup_samples(partyIdx, ios, enc, eval, runtime);

	// encrypt (only parties 0,1 provide input)
	u64 rows = values.size();
	std::vector<si64> A(rows);
	std::vector<si64> B(rows);

	// note: this fails if you try to make multiple local/remote calls in the same if/else statement
	// maybe could fix this with tasks?
	for (int i = 0; i < 10; i++)
	{
		if (partyIdx == 0)
		{
			enc.localInt(runtime, values[i], A[i]).get();
		}
		else
		{
			enc.remoteInt(runtime, A[i]).get();
		}

		if (partyIdx == 1)
		{
			enc.localInt(runtime, values[i], B[i]).get();
		}
		else
		{
			enc.remoteInt(runtime, B[i]).get();
		}
	}

	// parallel multiplications
	std::vector<si64> prods(rows);
	Sh3Task task = runtime.noDependencies();
	for (u64 i = 0; i < rows; ++i)
		task = eval.asyncMul(task, B[i], A[i], prods[i]);
	task.get();

	// addition
	si64 sum = prods[0];
	for (u64 i = 1; i < rows; ++i)
		sum = sum + (si64)prods[i];

	// reveal result
	i64 result;
	enc.revealAll(runtime, sum, result).get();
	std::cout << "result: " << result << std::endl;
}
