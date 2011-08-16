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
#ifndef NN_HATNODE_H
#define NN_HATNODE_H

#include "binOpNode.h"

/**
 * @class hatNode
 *
 * @brief The parse tree node representing the left subtree to the power of the 
 *	right subtree
 */
class hatNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new hatNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::hat; } 

	virtual std::string str() const
	{
		return "(" + left->str() + ")^{" + right->str() + "}";
	}

	virtual std::string nice_str() const
	{
		if (left->isLeaf() || left->type() == nodeTypes::idx) 
			{ return left->str() + "^{" + right->nice_str() + "}"; }
		return "(" + left->nice_str() + ")^{" + right->nice_str() + "}";
	}

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* rtemp = right->collapse();
		eqnNode* outexpr;
		
		if (ltemp->type() == nodeTypes::num && rtemp->type() == nodeTypes::num && ((numNode*)rtemp)->get() > 0)
		{
			outexpr = new numNode(
	intPow(((numNode*)ltemp)->get(), ((numNode*)rtemp)->get())
				);
			delete ltemp;
			delete rtemp;
		}
		else if (rtemp->type() == nodeTypes::num && ((numNode*)rtemp)->get() == 0)
		{
			outexpr = new numNode(1);
			delete ltemp;
			delete rtemp;
		}
		else if (rtemp->type() == nodeTypes::num && ((numNode*)rtemp)->get() == 1)
		{
			outexpr = ltemp;
			delete rtemp;
		}
		else
		{
			outexpr = new hatNode(ltemp,rtemp);
			delete ltemp;
			delete rtemp;
		}
		return outexpr;
	}

	hatNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}
	virtual double value() const { return pow(getL()->value(),getR()->value()); }	
	virtual ~hatNode() { deleteAll(); }
};


#endif
