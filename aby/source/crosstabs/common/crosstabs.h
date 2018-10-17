/**
 \file 		crosstab.h
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

#ifndef __CROSSTAB_H_
#define __CROSSTAB_H_

#include "../../../abycore/circuit/booleancircuits.h"
#include "../../../abycore/circuit/arithmeticcircuits.h"
#include "../../../abycore/circuit/circuit.h"
#include "../../../abycore/aby/abyparty.h"
#include "../../../abycore/sharing/sharing.h"
#include <math.h>
#include <cassert>

using namespace std;
/*
struct ct_pair *build_pairs(uint32_t nvals);
void destroy_pairs(struct ct_pair *p);
*/


/**
 \param		role 		role played by the program which can be server or client part.
 \param 	address 	IP Address
 \param 	seclvl 		Security level
 \param 	nvals		Number of values
 \param 	bitlen		Bit length of the inputs
 \param 	nthreads	Number of threads
 \param		mt_alg		The algorithm for generation of multiplication triples
 \param 	sharing		Sharing type object
 \param 	num			the number of elements in the crosstabs arrays
 \brief		This function is used for running a testing environment for solving Crosstabs 
 */
const int32_t BINS = 5;
int32_t test_crosstabs_circuit(e_role role, char* address, uint16_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, uint32_t num);

/**
 \param		s_x			share of X values
 \param		s_y 		share of Y values
 \param 	num			the number of elements in the crosstabs arrays
 \param		ac	 		Arithmetic Circuit object.
 \brief		This function is used to build and solve Crosstabs modulo 2^16. 
 
It computes the crosstabs product by
 	 	 	multiplying each value in x and y, and adding those multiplied results to evaluate the inner
 	 	 	product. The addition is performed in a tree, thus with logarithmic depth.
 */

vector<share *>BuildVectorCrosstabsCircuit(vector<share*> xids, 
                                   vector<share*> xvals, 
                                   vector<share*> yids, 
                                   vector<share*> yvals,
                                   vector<share*> numbers,
                                   vector<share*> results,
        ArithmeticCircuit *circ, BooleanCircuit *yao_circ, BooleanCircuit *bool_circ);

#endif
