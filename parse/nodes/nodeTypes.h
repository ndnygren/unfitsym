/* unfitsym - framework for symbolic computation
* Copyright (C) 2011 Nick Nygren
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>. */
#ifndef NN_NODETYPES_H
#define NN_NODETYPES_H


/**
 * @class nodeTypes
 *
 * @brief Integer codes representing the non-pure-virtual node types
 *
 */

class nodeTypes
{
	public:
	static const int num = 1;
	static const int sum = 2;
	static const int sub = 3;
	static const int prod = 4;
	static const int var = 5;
	static const int frac = 6;
	static const int neg = 7;
	static const int hat = 8;
	static const int deriv = 9;
	static const int integral = 10; // indefinite integrals
	static const int sin = 11;
	static const int cos = 12;
	static const int ln = 13;
	static const int integralb = 14; // definite integrals
	static const int idx = 15;
};


#endif
