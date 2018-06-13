/**
 \file 		crosstabs.cpp
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
 \brief		Implementation of Crosstabs using ABY Framework.
 */

#include "crosstabs.h"

int32_t test_crosstabs_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
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

    BooleanCircuit *yao_circ = (BooleanCircuit *) 
          sharings[S_YAO]->GetCircuitBuildRoutine();

    BooleanCircuit *bool_circ = (BooleanCircuit *) 
          sharings[S_BOOL]->GetCircuitBuildRoutine();

	/**
	 Step 4: Creating the share objects - s_x_vec, s_y_vec which
	 are used as inputs to the computation. Also, s_out which stores the output.
	 */

	//share *s_x_keys, *s_x_values, *s_y_keys, *s_y_values, *s_out;
    share *s_out;

	/**
	 Step 5: Allocate the xvals and yvals that will hold the plaintext values.
	 */
	uint16_t x, y;

	uint16_t output, v_sum = 0;

    vector<share *> xvals(num, NULL);
    vector<share *> yvals(num, NULL);
    vector<share *> xids(num, NULL);
    vector<share *> yids(num, NULL);

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
	for (i = 0; i < num; i++) {
		x = rand();
		y = rand();

		v_sum += x;

        xvals[i] = circ->PutINGate(x, bitlen, SERVER);
        yvals[i] = circ->PutINGate(y, bitlen, CLIENT);

        xids[i]  = bool_circ->PutINGate(i, bitlen, SERVER);
        yids[i]  = bool_circ->PutINGate(i, bitlen, CLIENT);
	}


	/**
	 Step 7: Call the build method for building the circuit for the
	 problem by passing the shared objects and circuit object.
	 Don't forget to type cast the circuit object to type of share
	 */

    s_out = BuildVectorCrosstabsCircuit(xids, xvals, yids, yvals, 
            circ, yao_circ, bool_circ);
    cout << "finished building circuit" << endl;

	/**
	 Step 8: Output the value of s_out (the computation result) to both parties
	 */
    s_out = circ->PutOUTGate(s_out, ALL);
    cout << "placed out gate" << endl;

	/**
	 Step 9: Executing the circuit using the ABYParty object evaluate the
	 problem.
	 */
	party->ExecCircuit();

	/**
	 Step 10: Type caste the plaintext output to 16 bit unsigned integer.
	 */
	output = s_out->get_clear_value<uint32_t>();

	cout << "\nCircuit Result: " << output;
	cout << "\nVerification Result: " << v_sum << endl;

	delete party;

	return 0;
}

share *BuildSimpleCrosstabsCircuit(share *s_xkeys, share *s_ykeys,
                                   ArithmeticCircuit *ac,
                                   BooleanCircuit *yc,
                                   BooleanCircuit *bc){
    s_xkeys = yc->PutADDGate(s_xkeys, s_ykeys);
    s_xkeys = bc->PutY2AGate(s_xkeys,bc);
    return s_xkeys;
}


share *BuildVectorCrosstabsCircuit(vector<share*> xids, 
                                   vector<share*> xvals, 
                                   vector<share*> yids, 
                                   vector<share*> yvals,
        ArithmeticCircuit *circ, BooleanCircuit *yao_circ, BooleanCircuit *bool_circ) {

    vector<share *> eqs(xids.size() * yids.size(), NULL);
    for(int i=0; i<xids.size(); i++) {
        for(int j=0; j<yids.size(); j++) {
            int idx = i*xids.size() + j;
            // check if ids match
            eqs[idx] = bool_circ->PutEQGate(xids[i], yids[j]);
            
            // TODO bins go here
            // if so, count xval
            eqs[idx] = bool_circ->PutMULGate(eqs[idx], xvals[i]);
            circ->PutPrintValueGate(eqs[idx], "idxth added value");
            // store the total sum in index 0
            eqs[0] = bool_circ->PutADDGate(eqs[0], eqs[idx]);
        }
    }
    eqs[0] = circ->PutB2AGate(eqs[0]);
    return eqs[0];
}

/*
 Constructs the crosstabs product circuit. num multiplications and num additions.
 */
share* BuildCrosstabsCircuit(share *s_xkeys, share *s_xvals, 
                             share *s_ykeys, share *s_yvals, 
                             uint32_t num, ArithmeticCircuit *ac,
                             BooleanCircuit *yc,
                             BooleanCircuit *bc) {
	uint32_t i,j,k;
    uint32_t bins = 3; // this should come from somewhere

    share *s_sum;

    s_xkeys = ac->PutSplitterGate(s_xkeys);
    s_xvals = ac->PutSplitterGate(s_xvals);
    s_ykeys = ac->PutSplitterGate(s_ykeys);
    s_yvals = ac->PutSplitterGate(s_yvals);

    s_xkeys = yc->PutA2YGate(s_xkeys);
    s_ykeys = yc->PutA2YGate(s_ykeys);
    share *s_idmatch = yc->PutEQGate(s_xkeys, s_ykeys);

    yc->PutPrintValueGate(s_idmatch, "everything matches?");


    for (i = 0; i < num; i++) {
      for (j = 0; j < num; j++) {
        /* broken
        uint32_t ti = ac->PutEQGate(s_xkeys->get_wire_id(i), s_ykeys->get_wire_id(j));
        ti = ac->PutMULGate(ti, s_xvals->get_wire_id(i));
        s_sum->set_wire_id(0, ac->PutADDGate(s_sum, ti)); 
        */
          
        // TODO bins
      }
    }

    return s_sum;

}
