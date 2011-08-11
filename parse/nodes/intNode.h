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
#ifndef NN_INTNODE_H
#define NN_INTNODE_H

#include "binOpNode.h"

/**
 * @class intNode 
 * 
 * @brief Parse tree node representing the integral of the left subtree,
 * 	with respect to the variable in the right subtree (without boundaries).
 * 
 */

class intNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new intNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::integral; } 

	/*
	 * virtual std::string str() const
	 *
	 * The standard LaTeX syntax for a integral.
	 */
	virtual std::string str() const
	{
		return "\\int " + left->str() + " d{" + right->str()+ "}";
	}

	virtual int size() const
	{
		return getL()->size();
	}

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* rtemp = right->collapse();
		eqnNode* outexpr;
		
		outexpr = new intNode(ltemp,rtemp);
		delete ltemp;
		delete rtemp;

		return outexpr;
	}

	intNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}
	virtual double value() const { return getL()->value(); }
	virtual ~intNode() { deleteAll(); }
};


#endif
