/**
 \file 		eqtest.cpp
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
 \brief		Implementation of eqtest using ABY Framework.
 */

#include "eqtest.h"

int32_t test_eqtest_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, uint32_t num) {

	/**
	  Set up party and circuit objects 
	 */
	ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads,
			mt_alg);
	vector<Sharing*>& sharings = party->GetSharings();

	ArithmeticCircuit* circ =
			(ArithmeticCircuit*) sharings[S_ARITH]->GetCircuitBuildRoutine();

    BooleanCircuit *yao_circ = (BooleanCircuit *) 
          sharings[S_YAO]->GetCircuitBuildRoutine();

    BooleanCircuit *bool_circ = (BooleanCircuit *) 
          sharings[S_BOOL]->GetCircuitBuildRoutine();

    share *s_out;
	srand(time(NULL));

    /**
     * Two test options; uncomment whichever you want to try
     */
    /*
    cout << "0/1 Test: expects arith and bool values to be the same (mod 2^l)"
         << endl
         << "bitlen: " << bitlen << endl << "-----" << endl;
    s_out = Run01Test(bitlen, circ, yao_circ, bool_circ, party);
    */

    cout << "Commutative Square Test: expects all sum values to be equal (mod 2^l)"
         << endl
         << "bitlen: " << bitlen << endl << "-----" << endl;
    s_out = RunCommutativeSquareTest(bitlen, circ, yao_circ, bool_circ, party);

	delete party;
	return 0;
}

/**
 * Tests conversion of shares with values 0/1
 * Each party inputs 0 and 1, plus two constant inputs 0 and 1
 * The circuit converts from a boolean share to an arithmetic share 
 * It prints the values before and after
 * Fails for all bitlens
 */
share *Run01Test(uint32_t bitlen, 
                ArithmeticCircuit *circ, 
                BooleanCircuit *yao_circ,
                BooleanCircuit *bool_circ,
                ABYParty *party) {
    
    uint16_t z = 0;
    uint16_t o = 1;
    share *x0 = bool_circ->PutINGate(z, bitlen, SERVER);
    share *y0 = bool_circ->PutINGate(z, bitlen, CLIENT);
    share *x1 = bool_circ->PutINGate(o, bitlen, SERVER);
    share *y1 = bool_circ->PutINGate(o, bitlen, CLIENT);
    share *zero= bool_circ->PutCONSGate(z, bitlen);
    share *one = bool_circ->PutCONSGate(o, bitlen);

    Build01TestCircuit(x0, y0, x1, y1, zero, one,
        circ, yao_circ, bool_circ, party);
}

/**
 * this always works when there is only one B2A gate
 * (try commenting out 5 of the sections)
 * behavior varies with more, though
 */
void Build01TestCircuit(share *x0, share *y0, share *x1, share *y1,
        share * zero, share * one,
        ArithmeticCircuit *circ, 
        BooleanCircuit *yao_circ, 
        BooleanCircuit *bool_circ,
        ABYParty *party) {

    x0 = circ->PutB2AGate(x0);
    x0 = circ->PutOUTGate(x0, ALL);

    y0 = circ->PutB2AGate(y0);
    y0 = circ->PutOUTGate(y0, ALL);

    x1 = circ->PutB2AGate(x1);
    x1 = circ->PutOUTGate(x1, ALL);

    y1 = circ->PutB2AGate(y1);
    y1 = circ->PutOUTGate(y1, ALL);

    zero = circ->PutB2AGate(zero);
    zero = circ->PutOUTGate(zero, ALL);

    one = circ->PutB2AGate(one);
    one = circ->PutOUTGate(one, ALL);

    party->ExecCircuit();

    int output = x0->get_clear_value<uint16_t>();
    cout << "x0: " << output << endl;
    output = y0->get_clear_value<uint16_t>();
    cout << "y0: " << output << endl;
    output = x1->get_clear_value<uint16_t>();
    cout << "x1: " << output << endl;
    output = y1->get_clear_value<uint16_t>();
    cout << "y1: " << output << endl;
    output = zero->get_clear_value<uint16_t>();
    cout << "zero: " << output << endl;
    output = one->get_clear_value<uint16_t>();
    cout << "one: " << output << endl;
    
    //circ->PutPrintValueGate(one, "arith one");
}


/**
 * test commutative property for sum and B2A
 * fails with 16, 8-bit inputs, not 32 or 64
 */
share *RunCommutativeSquareTest(uint32_t bitlen,
                                ArithmeticCircuit *circ, 
                                BooleanCircuit *yao_circ,
                                BooleanCircuit *bool_circ,
                                ABYParty *party) {
    uint16_t a,b,c,d,e;
    a = rand();
    b = rand();
    c = rand();
    d = rand();
 
    //cout << "a " << a << "\nb " << b << "\nc " << c << "\nd " << d << endl;
    uint16_t predicted = a + b + c + d ;
    cout << "Expected Result: " << predicted << endl;

    share *s_a = bool_circ->PutINGate(a, bitlen, SERVER);
    share *s_b = bool_circ->PutINGate(b, bitlen, CLIENT);
    share *s_c = bool_circ->PutINGate(c, bitlen, CLIENT);
    share *s_d = bool_circ->PutINGate(d, bitlen, CLIENT);

    BuildCommutativeSquareCircuit(s_a, s_b, s_c, s_d,
                                  circ, yao_circ, bool_circ, party);
}


/**
 * builds a commutative square circuit
 * A2B ( sum (a,b,c,d) ) = sum ( A2B (a,b,c,d) )
 *
 * commented out lines are for examining intermediate values
 */
void BuildCommutativeSquareCircuit(share *a_bool, share *b_bool, 
                                    share *c_bool, share *d_bool,
                                    ArithmeticCircuit *circ, 
                                    BooleanCircuit *yao_circ, 
                                    BooleanCircuit *bool_circ,
                                    ABYParty *party) {

    share *a_arith, *b_arith, *c_arith, *d_arith, *e_arith;

    share *bool_sum = bool_circ->PutADDGate(a_bool, b_bool);
    bool_sum = bool_circ->PutADDGate(bool_sum, c_bool);
    bool_sum = bool_circ->PutADDGate(bool_sum, d_bool);

    bool_sum = circ->PutB2AGate(bool_sum);
    bool_sum = circ->PutOUTGate(bool_sum, ALL);

    a_arith = circ->PutB2AGate(a_bool);
    b_arith = circ->PutB2AGate(b_bool);
    c_arith = circ->PutB2AGate(c_bool);
    d_arith = circ->PutB2AGate(d_bool);

    share * arith_sum = circ->PutADDGate(a_arith, b_arith);
    arith_sum = circ->PutADDGate(arith_sum, c_arith);
    arith_sum = circ->PutADDGate(arith_sum, d_arith);
    arith_sum = circ->PutOUTGate(arith_sum, ALL);

    party->ExecCircuit();
    uint16_t output = bool_sum->get_clear_value<uint16_t>();
    cout << "bool sum: " << output << endl;
    output = arith_sum->get_clear_value<uint16_t>();
    cout << "arith sum: " << output << endl;

}

