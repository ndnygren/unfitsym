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
#ifndef NN_FRACPARSE_H
#define NN_FRACPARSE_H

#include "../nodes/eqnNode.h"
#include "../nodes/fracNode.h"
#include "expParse.h"

/*
 * class fracParse
 * 
 * the CFG rule Expr -> "\frac" Curl Curl
 * Parses fractions
 */

class fracParse : public parsePart
{
	public:
	virtual void loadString(int offset, const std::string& data, int cap);
	virtual ~fracParse() { deleteAll(); }
};

#endif
