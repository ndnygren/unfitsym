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
#ifndef NN_INTPARSE_H
#define NN_INTPARSE_H

#include "expParse.h"

/**
 * @class intParse
 *
 * @brief The CFG rule Expr -> "\int" Expr "d{" Expr "}"
 * @details Parses integrals
 * Has been expanded to parse definite and indefinite integrals, the bounds on the integrals may be placed in either order as well.
 */
class intParse : public parsePart
{
	public:
	virtual void loadString(int offset, const std::string& data, int cap);
	virtual ~intParse() { deleteAll(); }
};

#endif
