/*
 * Sharemind MPC example programs
 * Copyright (C) 2018 Marcella Hastings
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
import oblivious;

domain pd_shared3p shared3p;

void main() {


	pd_shared3p uint64 [[1]] xids= argument("xids");
    pd_shared3p uint64 [[1]] xbins= argument("xbins");
    pd_shared3p uint64 [[1]] yids= argument("yids");
    pd_shared3p uint64 [[1]] yvals= argument("yvals");
	
    pd_shared3p uint64 [[1]] binsums(5) = 0;
    pd_shared3p bool same_id;
    pd_shared3p bool same_bin;
    pd_shared3p uint64 zero = 0;
    
    for( uint i=0; i<10; i++) {
        for( uint j=0; j<10; j++) {
            same_id = (xids[i] == yids[j]);
            for( uint k=0; k<5; k++) {
                same_bin = (xbins[i] == k);
                binsums[k] += choose(same_id & same_bin, yvals[j], zero);
            }
        }
    }

    publish("binsums", binsums);
}
