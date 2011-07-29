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

/*
 * class hatNode
 *
 * The parse tree node representing the left subtree to the power of the 
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

	hatNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}
	virtual double value() const { return pow(getL()->value(),getR()->value()); }	
	virtual ~hatNode() { deleteAll(); }
};


#endif
