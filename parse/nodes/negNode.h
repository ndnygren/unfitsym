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
#ifndef NN_NEGNODE_H
#define NN_NEGNODE_H

#include "monoOpNode.h"

/*
 * class negNode
 *
 * Monic operator, representing the negative of the subtree it contains
 */
class negNode : public monoOpNode
{
	public:
	//this nodes size is ignored as long as it does not occur twice in a row. This will be modified in the future, when a proper metric will make this distinction.
	virtual int size() const
	{
		if (getR()->type()==nodeTypes::neg) 
		{ return getR()->size() + 2; }
		return getR()->size();
	}

	virtual std::string str() const
	{
		return "-" + right->str();
	}

	virtual eqnNode* copy() const
	{
		return new negNode(right);
	}

	virtual int type() const { return nodeTypes::neg; }
	negNode(eqnNode* input) { right = input->copy(); }
	virtual double value() const { return -(getR()->value()); }
	virtual ~negNode() { deleteAll(); }

};


#endif
