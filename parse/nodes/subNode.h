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
#ifndef NN_SUBNODE_H
#define NN_SUBNODE_H

#include "binOpNode.h"

/**
 * @class subNode
 * 
 * @brief The parse tree node representing the subtraction of the right subtree 
 *	from the left subtree.
 */
class subNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const
		{ return new subNode(getL(), getR()); }

	virtual int type() const { return nodeTypes::sub; }

	virtual std::string str() const 
		{ return "(" + left->str() + "-" + right->str() + ")"; }

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* rtemp = right->collapse();
		eqnNode* outexpr;
		
		if (ltemp->type() == nodeTypes::num && rtemp->type() == nodeTypes::num)
		{
			outexpr = new numNode(((numNode*)ltemp)->get()
						- ((numNode*)rtemp)->get());
			delete ltemp;
			delete rtemp;
		}
		else if (rtemp->type() == nodeTypes::num && ((numNode*)rtemp)->get() == 0)
		{
			outexpr = ltemp;
			delete rtemp;
		}
		else
		{
			outexpr = new subNode(ltemp,rtemp);
			delete ltemp;
			delete rtemp;
		}
		return outexpr;
	}

	subNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}

	virtual double value() const { return getL()->value() - getR()->value(); }
	virtual ~subNode() { deleteAll(); }
};


#endif
