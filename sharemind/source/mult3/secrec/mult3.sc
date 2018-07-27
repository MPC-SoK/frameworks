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

domain pd_shared3p shared3p;


void main() {
	pd_shared3p uint64 ai = argument("ai");
	pd_shared3p uint64 bi = argument("bi");
	pd_shared3p uint64 ci = argument("ci");

    pd_shared3p uint64 product = ai * bi * ci;

    publish("product", product);
}
