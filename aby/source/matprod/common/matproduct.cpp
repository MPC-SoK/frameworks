/**
 \file 		innerproduct.cpp
 \author 	sreeram.sadasivam@cased.de
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

#include "matproduct.h"

int32_t test_matrix_product_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, uint32_t n, uint32_t m, uint32_t t) {

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
	ArithmeticCircuit* circ =
			(ArithmeticCircuit*) sharings[sharing]->GetCircuitBuildRoutine();

	/**
	 Step 4: Creating the share objects - s_x_vec, s_y_vec which
	 are used as inputs to the computation. Also, s_out which stores the output.
	 */

	share **s_x_vec, **s_y_vec, **s_out;
	s_x_vec = (share **) malloc(n*m * sizeof(share *));
	s_y_vec = (share **) malloc(m*t * sizeof(share *));
	s_out = (share **) malloc(n*t * sizeof(share *));

	/**
	 Step 5: Allocate the xvals and yvals that will hold the plaintext values.
	 */
	uint16_t *xvals = (uint16_t*) malloc(n*m * sizeof(uint16_t));
	uint16_t *yvals = (uint16_t*) malloc(m*t * sizeof(uint16_t));
	uint16_t *output = (uint16_t*) malloc(n*t * sizeof(uint16_t));
	uint16_t *v_output = (uint16_t*) malloc(n*t * sizeof(uint16_t));

	uint32_t i,j,k;
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

	for (i = 0; i < n*m; i++) {
			xvals[i] = rand();
			s_x_vec[i] = circ->PutINGate(xvals[i], bitlen, CLIENT);
	}
	for (i = 0; i < m*t; i++) {
			yvals[i] = rand();
			s_y_vec[i] = circ->PutINGate(yvals[i], bitlen, SERVER);
	}

	for( i=0;i<n;i++) {
		for(j=0;j<t;j++ ){
			v_output[i*t+j] = 0;
			for( k=0; k<m;k++ ) {
				v_output[i*t+j] += xvals[i*m+k]*yvals[k*t+j];
			}
		}
	}

	/**
	 Step 7: Call the build method for building the circuit for the
	 problem by passing the shared objects and circuit object.
	 Don't forget to type cast the circuit object to type of share
	 */
	BuildMatrixProductCircuit(s_out, s_x_vec, s_y_vec, n, m, t, (ArithmeticCircuit*) circ);

	/**
	 Step 8: Output the value of s_out (the computation result) to both parties
	 */
	for(i=0;i<n*t;i++){
		s_out[i] = circ->PutOUTGate(s_out[i], ALL);
	}

	/**
	 Step 9: Executing the circuit using the ABYParty object evaluate the
	 problem.
	 */
	party->ExecCircuit();

	/**
	 Step 10: Type caste the plaintext output to 16 bit unsigned integer.
	 */
	for( i=0; i<n*t; i++ ) {
		output[i] = s_out[i]->get_clear_value<uint16_t>();
	}


	cout << "\nCircuit Result: "; 
	for( i=0; i<n*t; i++ ) {
		cout << output[i] << " ";
	}
	cout << endl << endl;
	cout << "\nVerification Result: "; 
	for( i=0; i<n*t; i++ ) {
		cout << v_output[i]  << " ";
	}

	delete s_x_vec;
	delete s_y_vec;
	delete party;

	return 0;
}

/*
 Constructs the inner product circuit. num multiplications and num additions.
 */
void BuildMatrixProductCircuit(share **s_z, share **s_x, share **s_y, uint32_t n, uint32_t m, uint32_t t, ArithmeticCircuit *ac) {
	uint32_t i,j,k;
	share *tmp;

	for( i=0;i<n;i++) {
		for(j=0;j<t;j++ ){
			s_z[i*t+j] = ac->PutMULGate(s_x[i*m+0], s_y[0*t+j]);
			for( k=1; k<m;k++ ) {
				tmp = ac->PutMULGate(s_x[i*m+k], s_y[k*t+j]);
				s_z[i*t+j] = ac->PutADDGate( tmp, s_z[i*t+j] ); 
			}
		}
	}

}
