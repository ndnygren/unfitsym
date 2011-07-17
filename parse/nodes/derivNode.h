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
#ifndef NN_DERIVNODE_H
#define NN_DERIVNODE_H

#include "binOpNode.h"

/*
 * class derivNode 
 * 
 * Parse tree node representing the derivative of the left subtree,
 * 	with respect to the variable in the right subtree.
 * 
 */

class derivNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new derivNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::deriv; } 

	/*
	 * virtual std::string str() const
	 *
	 * The standard LaTeX syntax for a derivative. A alternative
	 * 	will be added later to handle larger left subtrees
	 */
	virtual std::string str() const
	{
		if (left->isLeaf()) // the "small" format
		{return "\\frac{d" + left->str() + "}{d" + right->str() + "}";}
		else // the "large" format
		{return "\\frac{d}{d" + right->str() + "}(" + left->str()+")";}
	}

	/*
	 * virtual int size() const
	 * 
	 * The size here is distorted to guide the search in a 
	 *	favorable direction. This will be corrected later
	 * 	when a better metric is constructed.
	 */
	virtual int size() const
	{
		return (getL()->size()) * (getL()->size());
	}

	derivNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}
	
	virtual ~derivNode() { deleteAll(); }
};


#endif
