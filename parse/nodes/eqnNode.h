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
#ifndef NN_EQNNODE_H
#define NN_EQNNODE_H

#include "nodeTypes.h"
#include <cmath>
#include <string>

/*
 * class eqnNode
 *
 * The interface for nodes in the parse tree. This is a linked list tree
 *	and almost all operators on this tree work recursively.
 */

class eqnNode
{
	public:
	/*
	 * virtual void deleteAll()
	 *
	 * Recursively frees all the parse tree's memory.
	 */
	virtual void deleteAll() { };

	/*
	 * virtual eqnNode* copy()
	 *
	 * Recursively copies all subtrees, allocating memory 
	 * 	for a second copy of this tree.
	 */
	virtual eqnNode* copy() const = 0;

	/*
	 * virtual bool eq(eqnNode* input)
	 *
	 * Comparison operator. Compares this root node, to inputs root
	 * 	node, and recursively compares each subtree to inputs subtrees
	 */
	virtual bool eq(eqnNode* input) const = 0;

	/*
	 * virtual bool eqVal(eqnNode* input)
	 *
	 * Comparison operator. Attempts to reduce this expression to a single 
	 *	integer, and the same for input. True is returned iff the values match.
	 */
	virtual bool eqVal(eqnNode* input) const
	{
		if (isConst() && input->isConst())
			{ return value() == input->value(); }
		else
			{ return false; }
	}

	/*
	 * virtual double value()
	 *
	 * Attempts to reduce this expression to a single numeric value
	 */
	virtual double value() const = 0;

	/*
	 * virtual int size()
	 * 
	 * Returns the number of nodes in the parse tree
	 */
	virtual int size() const = 0;

	/*
	 * virtual int type()
	 *
	 * Returns an integer code representing the type. Codes are listed
	 * in parse/nodes/nodeTypes.h
	 */
	virtual int type() const = 0;

	/*
	 * virtual bool isLeaf()
	 * 
	 * Returns true only in the case of a "number" or "variable"
	 */
	virtual bool isLeaf() const { return false; }

	/*
	 * virtual std::string str()
	 * 
	 * Recursively forms the LaTeX formated string representing 
	 *	the parse tree
	 */
	virtual std::string str() const = 0;


	/*
	 * bool isConst()
	 *
	 * returns true iff the expression contains no variables
	 * 
	 */
	virtual bool isConst() const
		{ return true; }

	/*
	 * bool isConst(std::string name)
	 *
	 * returns true iff the expression does not contain the 
	 *	specified variable
	 * 
	 */
	virtual bool isConst(const std::string& name) const
	{
		if (name.length() > 0)
			{ return true; }
		return false;
	}

	/*
	 * bool isVar(std::string name)
	 *
	 * returns true iff the expression is the specified variable
	 * 
	 */
	virtual bool isVar(const std::string& name) const 
	{
		if (name.length() > 0)
			{ return false; }
		return false;
	}

	virtual ~eqnNode() { }
};


#endif
