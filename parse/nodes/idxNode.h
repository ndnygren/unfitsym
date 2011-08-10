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
#ifndef NN_IDXNODE_H
#define NN_IDXNODE_H

#include "binOpNode.h"
#include "numNode.h"

/**
 * @class idxNode
 *
 * @brief The parse tree node representing an index variable. The left subtree is a single variable, the right is a general expression
 */
class idxNode : public binOpNode
{
	public:
	virtual eqnNode* copy() const 
		{ return new idxNode(getL(), getR()); } 

	virtual int type() const { return nodeTypes::idx; } 

	virtual std::string str() const
	{
		return left->str() + "_{" + right->str() + "}";
	}

	virtual bool isConst() const
		{ return false; }

	virtual bool isConst(const std::string& name) const
		{ return getR()->isConst(name); }


	/**
	 * @brief quickly sets the index to a new integer
	 * @param newindex The new index
	 */
	void setIdx(int newindex)
	{
		delete getR();
		right = new numNode(newindex);
	}

	virtual int size() const { return getR()->size(); }

	idxNode(eqnNode* lin, eqnNode* rin)
	{
		left = lin->copy();
		right = rin->copy();
	}

	virtual double value() const { return 0.0; }

	virtual ~idxNode() { deleteAll(); }
};


#endif
