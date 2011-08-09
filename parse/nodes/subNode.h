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

	subNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}

	virtual double value() const { return getL()->value() - getR()->value(); }
	virtual ~subNode() { deleteAll(); }
};


#endif
