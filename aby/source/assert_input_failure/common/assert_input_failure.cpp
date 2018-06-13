/**
 \file 		innerproduct.cpp \author 	sreeram.sadasivam@cased.de
 \copyright	ABY - A Framework for Efficient Mixed-protocol Secure Two-party Computation
 Copyright (C) 2015 Engineering Cryptographic Protocols Group, TU Darmstadt
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Affero General Public License for more details.
 You should have received a copy of the GNU Affero General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 \brief		Implementation of the Inner Product using ABY Framework.
 */

#include "assert_input_failure.h"

int32_t test_assert_input_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, uint32_t n) {

	/**
	 Step 1: Create the ABYParty object which defines the basis of all the
	 operations which are happening.	Operations performed are on the
	 basis of the role played by this object.
	 */
	ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg);

	/**
	 Step 2: Get to know all the sharing types available in the program.
	 */
	vector<Sharing*>& sharings = party->GetSharings();

	/**
	 Step 3: Create the circuit object on the basis of the sharing type
	 being inputed.
	 */
	BooleanCircuit* yc = (BooleanCircuit*) sharings[S_YAO]->GetCircuitBuildRoutine();

	/**
	 Step 4: Creating the share objects - s_x_vec, s_y_vec which
	 are used as inputs to the computation. Also, s_out which stores the output.
	 */

	share **s_V, **s_out;
	s_V = (share **) malloc(n * sizeof(share *));
	s_out = (share **) malloc(n* sizeof(share *));

	/**
	 Step 5: Allocate the xvals and yvals that will hold the plaintext values.
	 */

	uint16_t num_out = n;
	uint16_t *V = (uint16_t*) malloc(n * sizeof(uint16_t));
	uint16_t *output = (uint16_t*) malloc(num_out * sizeof(uint16_t));

	uint32_t i;
	srand(time(NULL));

	/**
	 Step 6: Fill the arrays xvals and yvals with the generated random values.
	 Both parties use the same seed, to be able to verify the
	 result. In a real example each party would only supply
	 one input value. Copy the randomly generated vector values into the respective
	 share objects using the circuit object method PutINGate().
	 Also mention who is sharing the object.
	 The values for the party different from role is ignored,
	 but PutINGate() must always be called for both roles.
	 */

	for (i = 0; i < n; i++) {
		V[i] = rand();
		s_V[i] = yc->PutINGate(V[i], bitlen, CLIENT);
		yc->PutAssertGate( s_V[i], V[i], bitlen );
	}

	cout << "=======================" << endl;

	/*
	for( i=0;i<n;i++ ) {
		yc->PutAssertGate( s_V[i], V[i], bitlen );
	}
	*/
	
	//If you uncomment the line below, the AssertGate above fails!
	//s_V[0] = yc->PutADDGate(s_V[1],s_V[2]);

	share *tmp;
	for (i = 0; i < n; i++) {
		tmp = yc->PutADDGate(s_V[i],s_V[i]);
	}

	/**
	 Step 8: Output the value of s_out (the computation result) to both parties
	 */
	for(i=0;i<num_out;i++){
		s_out[i] = yc->PutOUTGate(s_V[i], ALL);
	}

	/**
	 Step 9: Executing the circuit using the ABYParty object evaluate the
	 problem.
	 */
	party->ExecCircuit();
	

	/**
	 Step 10: Type caste the plaintext output to 16 bit unsigned integer.
	 */
	for( i=0; i<num_out; i++ ) {
		output[i] = s_out[i]->get_clear_value<uint16_t>();
	}


	cout << "\nCircuit Result: "; 
	for( i=0; i<num_out; i++ ) {
		cout << output[i] << " ";
	}
	cout << endl << endl;

	cout << "\nVerification Result: "; 
	for( i=0; i<num_out; i++ ) {
		cout << V[i] << " ";
	}
	cout << endl << endl;

	delete V;
	delete s_V;
	delete party;

	return 0;
}


