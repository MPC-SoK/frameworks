/*
 * Sharemind MPC example programs
 * Copyright (C) 2018 MPC SoK
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **/

import stdlib;
import shared3p;

domain pd_shared3p shared3p;

void main() {


	pd_shared3p uint64 [[1]] xids= argument("xids");
    pd_shared3p uint64 [[1]] xbins= argument("xbins");
    pd_shared3p uint64 [[1]] yids= argument("yids");
    pd_shared3p uint64 [[1]] yvals= argument("yvals");
	

    pd_shared3p uint64 [[3]] eqcheck(10, 10, 5);

    for( uint i=0; i<10; i++) {
        for( uint j=0; j<10; j++) {
            for( uint k=0; k<5; k++) {
                eqcheck[i,j,k] = (uint64) ((xids[i] == yids[j]) & (xbins[i] == k));
            }
        }
    }

    for( uint i=0; i<10; i++) {
        for( uint k=0; k<5; k++) {
            eqcheck[i,0:10, k] = yvals * eqcheck[i,0:10, k];
        }
    }

    pd_shared3p uint64 [[1]] binsums(5) = 0;

    for( uint k=0; k<5; k++) {
        pd_shared3p uint64 ksum = 0;
        for(uint i=0; i<10; i++) {
            ksum += sum(eqcheck[i, 0:10, k]);
        }
        binsums[k] = ksum;
    }

    publish("binsums", binsums);
}
