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

#include "yc_max_index.h"

int32_t test_max_index_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
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

	share **s_V;
	uint16_t num_out = 1;
	s_V = (share **) malloc(n * sizeof(share *));
	share *s_max_ind;

	/**
	 Step 5: Allocate the xvals and yvals that will hold the plaintext values.
	 */
	uint16_t *V = (uint16_t*) malloc(n * sizeof(uint16_t));
	uint16_t output;

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

	int max_ind, max_val;
	max_ind = 0;
	max_val = 0;
	for (i = 0; i < n; i++) {
			V[i] = rand();
			if( V[i] > max_val ) {
				max_ind = i;
				max_val = V[i];
			}
			s_V[i] = yc->PutINGate(V[i], bitlen, CLIENT);
			//yc->PutAssertGate( s_V[i], V[i], bitlen ); //THIS ASSERTION FAILS (but if the ASSERTION in BuildMaxIndexCircuit is uncommented
	}

	//THESE ASSERTIONS FAIL!!
	for( i=0;i<n;i++ ) {
		yc->PutAssertGate( s_V[i], V[i], bitlen );
	}


	/**
	 Step 7: Call the build method for building the circuit for the
	 problem by passing the shared objects and circuit object.
	 Don't forget to type cast the circuit object to type of share
	 */
	s_max_ind = BuildMaxIndexCircuit( s_V, n,(BooleanCircuit*) yc);

	/**
	 Step 8: Output the value of s_out (the computation result) to both parties
	 */

	 s_max_ind = yc->PutOUTGate(s_max_ind,ALL );

	/**
	 Step 9: Executing the circuit using the ABYParty object evaluate the
	 problem.
	 */

	party->ExecCircuit();
	

	/**
	 Step 10: Type caste the plaintext output to 16 bit unsigned integer.
	*/

	output = s_max_ind->get_clear_value<uint16_t>();

	cout << "\nCircuit Result: " << output << endl << endl;

	cout << "\nVerification Result: " << max_ind << endl << endl;

	delete V;
	delete s_V;
	delete party;

	return 0;
}

/*
 Constructs a circuit to return the index of the maximum value in a list
 */
share *BuildMaxIndexCircuit(share **V,  uint32_t n, BooleanCircuit *yc) {
	uint16_t i;
	share *tmp;
	int bitlen = 16;
	share *tmp2;
	uint16_t zro = 0;

	share *max_val, *max_ind, *cur_ind;
	i=0;
	max_val = V[i];
	max_ind = yc->PutCONSGate( i, bitlen );
	for( i = 1; i< n; i++ ){
		tmp = yc->PutGTGate( max_val, V[i] );	
		//If you uncomment any of the three following PutPrintValueGates the PutAssertGate fails
		//yc->PutPrintValueGate( max_val, "max_val" );
		//yc->PutPrintValueGate( V[i], "cur_val" );
		//yc->PutPrintValueGate( tmp, "comparison" );
		max_val = yc->PutMUXGate( max_val, V[i], tmp );
		//tmp2 = yc->PutGTGate( V[i], max_val );
		//yc->PutAssertGate( tmp2, zro, bitlen );
		//yc->PutPrintValueGate( max_val, "new max_val" ); //If you uncomment this line, the PutAssertGate fails
		cur_ind = yc->PutCONSGate( (UGATE_T) i, bitlen );
		//cur_ind = yc->PutCONSGate( i, bitlen );
		//yc->PutPrintValueGate( cur_ind, "Current index" );

		//FAILURE
		//yc->PutAssertGate( cur_ind, i, bitlen ); //This assertion fails if some of the PutPrintValueGates above are uncommented

		max_ind = yc->PutMUXGate( max_ind, cur_ind, tmp );
	}
	
	return max_ind;

}

