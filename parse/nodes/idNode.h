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
#ifndef NN_IDNODE_H
#define NN_IDNODE_H

#include "binOpNode.h"

/**
 * @class idNode
 *
 * @brief The parse tree node representing the equality of the left and right subtrees. This is the most basic of all truth valued symbols. 
 */

class idNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new idNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::ident; } 

	virtual std::string str() const
	{
		return left->str() + "=" + right->str();
	}

	virtual std::string nice_str() const
	{
		return left->nice_str() + " = " + right->nice_str();
	}

	idNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* rtemp = right->collapse();
		eqnNode* outexpr = new idNode(ltemp,rtemp);
		
		delete rtemp;
		delete ltemp;

		return outexpr;
	}

	virtual double value() const { return 0; }	
	virtual ~idNode() { deleteAll(); }

	virtual eqnNode* new_node(eqnNode* linput, eqnNode* rinput) const
	{
		return new idNode(linput, rinput);
	}
};


#endif
