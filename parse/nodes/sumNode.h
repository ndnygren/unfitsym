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
#ifndef NN_SUMNODE_H
#define NN_SUMNODE_H

#include "binOpNode.h"

/**
 * @class sumNode
 *
 * @brief The parse tree node representing the addition of the left and right subtrees
 */

class sumNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new sumNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::sum; } 

	virtual std::string str() const
	{
		return "(" + left->str() + "+" + right->str() + ")";
	}

	virtual std::string nice_str() const
	{
		std::string outstr;
		if (left->type() == type() || left->isLeaf() || left->isMono() || 
			left->type() == nodeTypes::frac ||
			left->type() == nodeTypes::hat ||
			left->type() == nodeTypes::deriv ||
			left->type() == nodeTypes::integral ||
			left->type() == nodeTypes::integralb ||
			left->type() == nodeTypes::idx)
			{ outstr = left->nice_str() + " + "; }
		else
			{ outstr = "(" + left->nice_str() + ") + "; }
		
		if (right->type() == type() || right->isLeaf() || right->isMono() ||
			right->type() == nodeTypes::frac ||
			right->type() == nodeTypes::hat ||
			right->type() == nodeTypes::deriv ||
			right->type() == nodeTypes::integral ||
			right->type() == nodeTypes::integralb ||
			right->type() == nodeTypes::idx)
			{ outstr += right->nice_str(); }
		else
			{ outstr += "(" + right->nice_str() + ")"; }

		return outstr;
	}

	sumNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* rtemp = right->collapse();
		eqnNode* outexpr;
		
		if (ltemp->type() == nodeTypes::num && rtemp->type() == nodeTypes::num)
		{
			outexpr = new numNode(((numNode*)ltemp)->get()
						+ ((numNode*)rtemp)->get());
			delete ltemp;
			delete rtemp;
		}
		else if (ltemp->type() == nodeTypes::num && ((numNode*)ltemp)->get() == 0)
		{
			outexpr = rtemp;
			delete ltemp;
		}
		else if (rtemp->type() == nodeTypes::num && ((numNode*)rtemp)->get() == 0)
		{
			outexpr = ltemp;
			delete rtemp;
		}
		else
		{
			outexpr = new sumNode(ltemp,rtemp);
			delete ltemp;
			delete rtemp;
		}
		return outexpr;
	}

	virtual double value() const { return getL()->value() + getR()->value(); }	
	virtual ~sumNode() { deleteAll(); }
};


#endif
