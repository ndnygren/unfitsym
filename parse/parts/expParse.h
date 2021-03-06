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
#ifndef NN_EXPPARSE_H
#define NN_EXPPARSE_H

#include "cassetteMachine.h"
#include "parsePart.h"
#include "natParse.h"
#include "sumParse.h"
#include "subParse.h"
#include "varParse.h"
#include "prodParse.h"
#include "parenParse.h"
#include "curlyParse.h"
#include "fracParse.h"
#include "negParse.h"
#include "hatParse.h"
#include "derivParse.h"
#include "intParse.h"
#include "sineParse.h"
#include "cosineParse.h"
#include "lnParse.h"
#include "idxParse.h"
#include "tvarParse.h"

/**
 * @class expParse
 *
 * @brief parsePart responsible for recognizing an expression, in the 
 *	most general sense
 *
 * @details Alternately accepts sums, differences, fractions, and all 
 * other operators, including functions, derivatives, and integrals, recursing 
 * on all of these. The expParse, also includes numbers and variables, where 
 * recursion halts.
 */

class expParse : public parsePart
{
	public:
	virtual void loadString(int offset, const std::string& data, int cap);
	expParse();
	virtual ~expParse() { deleteAll(); }
};


#endif
