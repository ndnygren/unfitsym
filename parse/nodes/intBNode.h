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
#ifndef NN_INTBNODE_H
#define NN_INTBNODE_H

#include "intNode.h"

/**
 * @class intBNode 
 * 
 * @brief Parse tree node representing the definite integral of the left subtree,
 * 	with respect to the variable in the right subtree.
 * 
 */

class intBNode : public intNode
{
	protected:
	eqnNode* upper;
	eqnNode* lower;

	public:
	virtual eqnNode* copy() const 
		{ return new intBNode(getL(), getR(), getUpper(), getLower()); } 

	virtual int type() const { return nodeTypes::integralb; } 

	virtual std::string str() const
	{
		return "\\int_{"+ getLower()->str() + "}^{" + getUpper()->str() + "} " + left->str() + " d{" + right->str()+ "}";
	}

	virtual void deleteAll() 
	{
		if (left != 0)
		{
			left->deleteAll();
			delete left;
			left = 0;
		}
		if (right != 0)
		{
			right->deleteAll();
			delete right;
			right = 0;
		}
		if (upper != 0)
		{
			upper->deleteAll();
			delete upper;
			upper = 0;
		}
		if (lower != 0)
		{
			lower->deleteAll();
			delete lower;
			lower = 0;
		}
	}

	/**
	 * @brief standard getter function for upper bound
	 * @returns upper bound expression
	 */
	virtual eqnNode* getUpper() const {return upper;}

	/**
	 * @brief standard getter function for lower bound
	 * @returns lower bound expression
	 */
	virtual eqnNode* getLower() const {return lower;}

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* outexpr;
		
		outexpr = new intBNode(ltemp, getR(), getUpper(), getLower());
		delete ltemp;

		return outexpr;
	}

	intBNode(eqnNode* lin, eqnNode* rin, eqnNode* upin, eqnNode* lowin) : intNode(lin,rin)
	{
		upper = upin->copy();
		lower = lowin->copy();
	}
	virtual ~intBNode() { deleteAll(); }
};


#endif
