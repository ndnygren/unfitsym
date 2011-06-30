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
#ifndef NN_NUMNODE_H
#define NN_NUMNODE_H

#include <sstream>
#include "leafNode.h"

class numNode : public leafNode
{
	protected:
	int num;

	std::string toString(int input) const
	{
		std::stringstream sstemp;
		sstemp << input;
		return sstemp.str();
	}

	public:
	virtual eqnNode* copy() const
		{ return new numNode(get()); }

	virtual int type() const
		{ return types.num; }

	int get() const { return num; }
	virtual std::string str() const { return toString(num); }

	numNode(int input) { num = input; }
};


#endif
