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
#ifndef NN_MONOOPNODE_H
#define NN_MONOOPNODE_H

#include "eqnNode.h"

/*
 * class MonoOpNode
 *
 * Pure virutal base for Monic operators
 */
class monoOpNode : public eqnNode
{
	protected:
	eqnNode* right; //only one subtree

	public:
	virtual bool eq(eqnNode* input) const
	{
		if (type() != input->type())
			{ return false; }

		return getR()->eq(((monoOpNode*)input)->getR());
	}


	//this nodes size is ignored as long as it does not occur twice in a row. This will be modified in the future, when a proper metric will make this distinction.
	virtual int size() const
	{
		return getR()->size() + 1;
	}

	virtual void deleteAll() 
	{
		if (right != 0)
		{
			right->deleteAll();
			delete right;
			right = 0;
		}
	}

	eqnNode* getR() const { return right; }

	/*
	 * bool isConst()
	 *
	 * returns true iff the expression contains no variables
	 * 
	 */
	virtual bool isConst() const
		{ return getR()->isConst(); }

	/*
	 * bool isConst(std::string name)
	 *
	 * returns true iff the expression does not contain the 
	 *	specified variable
	 * 
	 */
	virtual bool isConst(const std::string& name) const
		{ return getR()->isConst(name); }
};


#endif
