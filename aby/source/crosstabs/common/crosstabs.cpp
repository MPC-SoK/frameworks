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
		e_sharing sharing, uint32_t array_len) {

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
	 Step 5: Allocate the xvals and ybins that will hold the plaintext values.
	 */
	uint32_t x, y;

	uint32_t output;

        vector<share *> xvals(array_len, NULL);
        vector<share *> ybins(array_len, NULL);
        vector<share *> xids(array_len, NULL);
        vector<share *> yids(array_len, NULL);

	srand(time(NULL));

	/**
	 Step 6: Fill the arrays xvals and ybins with the generated random values.
	 Both parties use the same seed, to be able to verify the
	 result. In a real example each party would only supply
	 one input value. Copy the randomly generated vector values into the respective
	 share objects using the circuit object method PutINGate().
	 Also mention who is sharing the object.
	 The values for the party different from role is ignored,
	 but PutINGate() must always be called for both roles.
	 */
	vector<uint32_t> expected_results(BINS,0);
        uint32_t i;
	for (i = 0; i < array_len; i++) {
	    x = rand();
	    y = rand() % BINS;
   	    expected_results[y] += x;

            xvals[i] = circ->PutINGate(x, bitlen, SERVER);
            ybins[i] = bool_circ->PutINGate(y, bitlen, CLIENT);

            xids[i]  = bool_circ->PutINGate(i, bitlen, SERVER);
            yids[i]  = bool_circ->PutINGate(i, bitlen, CLIENT);
	}

	cout << "Filled in values..." << endl;
        uint8_t zero = 0;

        // initialize result bins to 0 and constant bin numbers
        // (constant input gates don't seem to be implemented)
        vector<share *> results(BINS, NULL);
        vector<share *> numbers(BINS,NULL);
        for (uint32_t i=0; i<BINS; i++) {
            numbers[i] = bool_circ->PutINGate(i,32,SERVER);
            results[i] = circ->PutINGate(zero,32,SERVER);
        }


	/**
	 Step 7: Call the build method for building the circuit for the
	 problem by passing the shared objects and circuit object.
	 Don't forget to type cast the circuit object to type of share
	 */

        vector<share *>s_out = BuildVectorCrosstabsCircuit(xids, xvals, yids, ybins, 
            numbers, results, circ, yao_circ, bool_circ);
 	cout << "Built circuit... " << endl;

	/**
	 Step 8: Output the value of s_out (the computation result) to both parties
	 **/
        for(int i=0; i<BINS; i++) {
            s_out[i] = circ->PutOUTGate(s_out[i], ALL);
        }
        cout << "placed out gates" << endl;
        party->ExecCircuit();
        cout << "Executed circuit" << endl;

        for(int i=0; i<BINS; i++) {
            output = s_out[i]->get_clear_value<uint32_t>();
            cout << "Bin " << i << ":\t" << output << endl;
            cout << "Expect:\t" << expected_results[i] << endl;
        }

        delete party;
    
        return 0;
}


vector<share *>BuildVectorCrosstabsCircuit(vector<share*> xids, 
                                   vector<share*> xvals, 
                                   vector<share*> yids, 
                                   vector<share*> ybins,
	vector<share*> numbers, vector<share*>results,
        ArithmeticCircuit *circ, BooleanCircuit *yao_circ, BooleanCircuit *bool_circ) {

    share *idmatch, *binmatch; 
    circ->PutPrintValueGate(results[0], "initial result");
    
    for(int i=0; i<xids.size(); i++) {
 	bool_circ->PutPrintValueGate(xids[i], "xid: ");
        for(int j=0; j<yids.size(); j++) {
 	    //bool_circ->PutPrintValueGate(yids[j], "yid: ");
            // check if ids match
            idmatch = bool_circ->PutEQGate(xids[i], yids[j]);
	    //bool_circ->PutPrintValueGate(idmatch, "idmatch "+to_string(i)+","+to_string(j));
	    for(int k=0; k<BINS; k++) {
                // check if bin matches
                binmatch = bool_circ->PutEQGate(numbers[k],ybins[j]);
                // if both id and bin match...
	        share *keep= bool_circ->PutANDGate(binmatch, idmatch); 
		keep = circ->PutB2AGate(keep);
		// add value to bin result
                keep = circ->PutMULGate(keep, xvals[i]);
                results[k] = circ->PutADDGate(results[k], keep);
	    	circ->PutPrintValueGate(results[k], to_string(k)+"th result in round "+to_string(i));
            }
        }
        bool_circ->PutPrintValueGate(xids[i], "done with round");
    }
    return results;
}

