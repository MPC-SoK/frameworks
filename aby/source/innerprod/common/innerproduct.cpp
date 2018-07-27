/**
 \file 		innerproduct.cpp
 \author 	sreeram.sadasivam@cased.de, heavily modified by marcella
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

#include "innerproduct.h"

int32_t test_inner_product_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, uint32_t num) {

	/**
	 Step 1: Create the ABYParty object which defines the basis of all the
	 operations which are happening.	Operations performed are on the
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

	share *s_x_vec, *s_y_vec, *s_out;

	/**
	 Step 5: Allocate the vectors that will hold the plaintext values.
	 */
	uint16_t x, y;

	uint16_t output;

	uint16_t * input = (uint16_t*) malloc(num * sizeof(uint16_t));

	uint32_t i;

	/**
	 Step 6: Fill the input array with data read from file.
	 Copy the input values into a share object for each party.
	 The values for the party different from role is ignored,
	 but PutINGate() must always be called for both roles.
	 */
    char *fname = (char *) malloc(100);
    sprintf(fname, "/root/ABY/src/examples/innerprod/data/innerprod.%d.dat", role);
    
    std::ifstream infile;
    infile.open(fname);
    
    for(i = 0; i < num; i++) {
        infile >> input[i] ;
        if(infile.eof()) {break;}
    }
    
    infile.close();

	s_x_vec = circ->PutSIMDINGate(i, input, 16, SERVER);
	s_y_vec = circ->PutSIMDINGate(i, input, 16, CLIENT);

	/**
	 Step 7: Build the circuit, passing the input shares and circuit object.
	 */
	s_out = BuildInnerProductCircuit(s_x_vec, s_y_vec, num, circ);

	/**
	 Step 8: Output the value of s_out (the computation result) to both parties
	 */
	s_out = circ->PutOUTGate(s_out, ALL);

	/**
	 Step 9: Executing the circuit using the ABYParty object evaluate the
	 problem.
	 */
	party->ExecCircuit();

	/**
	 Step 10: Type caste the plaintext output to 16 bit unsigned integer.
	 */
	output = s_out->get_clear_value<uint16_t>();

	cout << "Circuit Result: " << output << endl;

	delete s_x_vec;
	delete s_y_vec;
    delete input;
	delete party;

	return 0;
}

/*
 Constructs the inner product circuit. num multiplications and num additions.
 */
share* BuildInnerProductCircuit(share *s_x, share *s_y, uint32_t num, ArithmeticCircuit *ac) {
	uint32_t i;

	// pairwise multiplication of all input values
	s_x = ac->PutMULGate(s_x, s_y);

	// split SIMD gate to separate wires (size many)
	s_x = ac->PutSplitterGate(s_x);

	// add up the individual multiplication results and store result on wire 0
	// in arithmetic sharing ADD is for free, and does not add circuit depth, thus simple sequential adding
	for (i = 1; i < num; i++) {
		s_x->set_wire_id(0, ac->PutADDGate(s_x->get_wire_id(0), s_x->get_wire_id(i)));
	}

	// discard all wires, except the addition result
	s_x->set_bitlength(1);

	return s_x;
}
