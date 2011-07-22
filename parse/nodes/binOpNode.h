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
#ifndef NN_BINOPNODE_H
#define NN_BINOPNODE_H

#include "eqnNode.h"


/*
 * class binOpNode 
 * 
 *  virtual class describing parse tree nodes for binary operators.
 * (ex. addition, subtraction). Handles memory allocation details.
 * 
 * 
 */

class binOpNode : public eqnNode
{
	protected:
	eqnNode* left;
	eqnNode* right;

	/*
	 * int max(int left, int right) const
	 * 
	 *  returns the largest of {left,right}
	 */
	int max(int left, int right) const
	{
		if (left < right) { return right; }
		return left;
	}

	public:
	/*
	 * virtual bool eq(eqnNode* input) const
	 *
	 * Comparison function. Recursively comparse this parse
	 *	tree to the "input" parse tree.
	 */
	virtual bool eq(eqnNode* input) const
	{
		if (type() != input->type())
			{ return false; }

		return getR()->eq(((binOpNode*)input)->getR())
			&& getL()->eq(((binOpNode*)input)->getL());
	}


	/*
	 * virtual int size() const
	 * 
	 * Recursively counts the number of nodes in the parse tree
	 */
	virtual int size() const
	{
		return 1 + getR()->size() + getL()->size();
	}

	/*
	 * virtual void deleteAll() 
	 * 
	 * Recursively handles the deallocation of memory for the parse tree
	 */
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
	}

	// getL() returns the left subtree
	eqnNode* getL() const { return left; }
	// getR() returns the right subtree
	eqnNode* getR() const { return right; }

	/*
	 * bool isConst()
	 *
	 * returns true iff the expression contains no variables
	 * 
	 */
	virtual bool isConst() const
		{ return getL()->isConst() && getR()->isConst(); }

	/*
	 * bool isConst(std::string name)
	 *
	 * returns true iff the expression does not contain the 
	 *	specified variable
	 * 
	 */
	virtual bool isConst(const std::string& name) const
		{ return getL()->isConst(name) && getR()->isConst(name); }
};


#endif
