
#include "mult3.h"
#include <string>
#include <iostream>
using namespace std;

int32_t test_mult3_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, uint32_t num) {

	/**
	 Step 1: Create the ABYParty object which defines the basis of all the
	 operations which are happening. Operations performed are on the
	 basis of the role played by this object.
	 */
	ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads,
			mt_alg);

	/**
	 Step 2: Get to know all the sharing types available in the program.
	 */
	vector<Sharing*>& sharings = party->GetSharings();

	/**
	 Step 3: Create the circuit object on the basis of the sharing type
	 being inputed.
	 */
	ArithmeticCircuit* circ =
			(ArithmeticCircuit*) sharings[sharing]->GetCircuitBuildRoutine();

	/**
	 Step 4: Creating the share objects - s_x_vec, s_y_vec which
	 are used as inputs to the computation. Also, s_out which stores the output.
	 */

    share *i0, *i1, *i2, *s_out;
	uint16_t x, i, output;

	/**
	 Step 6: 
     Read secred shared data from file and put into circuit
	 */

    std::ifstream infile;
    char *fname = (char *) malloc(150);

    // open the data file corresponding to the correct party
    sprintf(fname, "/root/ABY/src/examples/mult3/data/mult3.%d.dat", role);

    // read data from file
    infile.open(fname);
    infile >> x;
    i0 = circ->PutSharedINGate(x,bitlen);
    infile >> x;
    i1 = circ->PutSharedINGate(x,bitlen);
    infile >> x;
    i2 = circ->PutSharedINGate(x,bitlen);
    infile.close();

    /**
      Step 7: Call the build method for the circuit, 
      passing the shared objects and circuit object.
     */
    s_out = BuildSharedMult3Circuit(i0, i1, i2, circ);

	/**
	 Step 9: Execute the circuit 
	 */
	party->ExecCircuit();

	/**
	 Step 10: Typecast the plaintext output to 16 bit unsigned integer.
	 */
	output = s_out->get_clear_value<uint16_t>();

	cout << "Circuit Result: " << output << endl;

    // clean up
    delete i0;
    delete i1;
    delete i2;
    delete fname;
	delete party;
	return 0;
}

// constructs a mult3 circuit
share * BuildSharedMult3Circuit(share *s_0, share *s_1, share *s_2,
                                ArithmeticCircuit *ac) {
    share *out = ac->PutMULGate(s_0, s_1);
    out = ac->PutMULGate(out, s_2);
    out = ac->PutOUTGate(out, ALL);
    return out;
}
