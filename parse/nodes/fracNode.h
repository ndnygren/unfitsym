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
#ifndef NN_FRACNODE_H
#define NN_FRACNODE_H

#include "binOpNode.h"

/**
 * @class fracNode 
 *
 * @brief the node representing the fraction of the left subtree over the right subtree
 */
class fracNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new fracNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::frac; } 

	virtual std::string str() const
	{
		return "\\frac{" + left->str() + "}{" + right->str() + "}";
	}

	virtual std::string nice_str() const
	{
		return "\\frac{" + left->nice_str() + "}{" + right->nice_str() + "}";
	}

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* rtemp = right->collapse();
		eqnNode* outexpr;
		
		if (ltemp->type() == nodeTypes::num && rtemp->type() == nodeTypes::num 
			&& ((numNode*)rtemp)->get()!=0
			&& ((numNode*)ltemp)->get() % ((numNode*)rtemp)->get()==0)
		{
			outexpr = new numNode(((numNode*)ltemp)->get()
						 / ((numNode*)rtemp)->get());
			delete ltemp;
			delete rtemp;
		}
		else if (ltemp->type() == nodeTypes::num && ((numNode*)ltemp)->get() == 0)
		{
			outexpr = ltemp;
			delete rtemp;
		}
		else if (rtemp->type() == nodeTypes::num && ((numNode*)rtemp)->get() == 1)
		{
			outexpr = ltemp;
			delete rtemp;
		}
		else
		{
			outexpr = new fracNode(ltemp,rtemp);
			delete ltemp;
			delete rtemp;
		}
		return outexpr;
	}

	fracNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}

	virtual double value() const 
	{
		if (getR()->value() != 0)
			{ return getL()->value() / getR()->value(); }
		else { return 0; }
	}
	virtual ~fracNode() { deleteAll(); }

	virtual eqnNode* new_node(eqnNode* linput, eqnNode* rinput) const
	{
		return new fracNode(linput, rinput);
	}
};


#endif
