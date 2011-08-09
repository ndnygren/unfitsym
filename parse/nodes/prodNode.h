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
#ifndef NN_PRODNODE_H
#define NN_PRODNODE_H

#include "binOpNode.h"

/**
 * @class prodNode
 *
 * @brief The parse tree node representing the product of the left subtree 
 * 	with the right subtree.
 */
class prodNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new prodNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::prod; } 

	virtual std::string str() const
	{
		return "(" + left->str() + "\\cdot " + right->str() + ")";
	}

	prodNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}

	virtual double value() const { return getL()->value() * getR()->value(); }
	virtual ~prodNode() { deleteAll(); }
};


#endif
