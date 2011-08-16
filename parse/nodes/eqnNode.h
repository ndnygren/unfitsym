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

/**
 * @class eqnNode
 *
 * @brief The interface for nodes in the parse tree. This is a linked list tree
 *	and almost all operators on this tree work recursively.
 */

class eqnNode
{
	public:
	// virtual void deleteAll()
	/**
	 *
	 * @brief Recursively frees all the parse tree's memory.
	 */
	virtual void deleteAll() { };

	//int intPow(int base, int arg)
	/**
	 * @brief quick integer exponentiation
	 * @param base the exponent base
	 * @param arg the exponent argument
	 * @returns base to the power argument in integer form
	 *
	 */
	static int intPow(int base, int arg)
	{
		int x = 0;
		if (arg == 1) { return base; }
		else if (arg == 0) { return 1; }
		else if (arg < 0) { return 0; } 
		else if (arg%2 == 0)
		{
			x = intPow(base, arg/2);
			return x*x;
		}

		x = intPow(base, (arg-1)/2);
		return x*x*base;
	}

	//virtual eqnNode* copy()
	/**
	 * @brief Recursively copies all subtrees, allocating memory 
	 * 	for a second copy of this tree.
	 * @returns a eqnNode* equal to the original, in new memory
	 */
	virtual eqnNode* copy() const = 0;

	// virtual bool eq(eqnNode* input)
	/**
	 * @brief Comparison operator. Compares this root node, to inputs root
	 * 	node, and recursively compares each subtree to inputs subtrees
	 * @param input a parse tree to be compared to *this
	 * @returns true iff input and *this have identical structure
	 */
	virtual bool eq(const eqnNode* input) const = 0;

	// virtual bool eqVal(eqnNode* input)
	/**
	 * @brief Comparison operator. Attempts to reduce this expression to a single 
	 *	integer, and the same for input. True is returned iff the values match.
	 * @param input a parse tree to be compared to *this
	 * @returns true iff input and *this have identical numeric value 
	 */
	virtual bool eqVal(eqnNode* input) const
	{
		if (isConst() && input->isConst())
			{ return value() == input->value(); }
		else
			{ return false; }
	}

	// virtual double value()
	/**
	 * @brief Attempts to reduce this expression to a single numeric value
	 * @returns the numeric value, if the expression is constant
	 */
	virtual double value() const = 0;

	// virtual int size()
	/**
	 * @brief Returns the number of nodes in the parse tree
	 * @returns integer size
	 */
	virtual int size() const = 0;

	// virtual int type()
	/**
	 * @brief Returns an integer code representing the type. Codes are listed
	 * in parse/nodes/nodeTypes.h
	 * @returns integer type code
	 */
	virtual int type() const = 0;

	// virtual bool isLeaf()
	/**
	 * @brief Returns true only in the case of a "number" or "variable"
	 */
	virtual bool isLeaf() const { return false; }

	// virtual bool isBin()
	/**
	 * @brief Returns true only in the case of a binary operator
	 */
	virtual bool isBin() const { return false; }

	// virtual bool isMono()
	/**
	 * @brief Returns true only in the case of a monic operator
	 */
	virtual bool isMono() const { return false; }

	// virtual std::string str()
	/**
	 * @brief Recursively forms the LaTeX formated string representing 
	 *	the parse tree
	 * @returns std::string in LaTeX format
	 */
	virtual std::string str() const = 0;


	// virtual std::string nice_str()
	/**
	 * @brief Recursively forms the LaTeX formated string representing 
	 *	the parse tree, except using brackets only where necessary
	 * @returns std::string in LaTeX format
	 */
	virtual std::string nice_str() const { return str(); }

	// bool isConst()
	/**
	 * @returns true iff the expression contains no variables
	 */
	virtual bool isConst() const
		{ return true; }

	// bool isConst(std::string name)
	/**
	 * @returns true iff the expression does not contain the 
	 *	specified variable
	 */
	virtual bool isConst(const std::string& name) const
	{
		if (name.length() > 0)
			{ return true; }
		return false;
	}

	// bool isVar(std::string name)
	/**
	 * @returns true iff the expression is the specified variable
	 */
	virtual bool isVar(const std::string& name) const 
	{
		if (name.length() > 0)
			{ return false; }
		return false;
	}

	/**
	 *@brief substitutes an expression for a string
	 *@param var the variable to be replaced
	 *@param expr the expression to replace it with
	 */
	virtual void replace(const std::string& var, eqnNode* expr) = 0;

	//eqnNode* collapse()
	/**
	 * @brief attempts to reduce the expression to a single numNode*
	 * @returns the collapsed expression
	 */
	virtual eqnNode* collapse() const = 0;

	virtual ~eqnNode() { }
};


#endif
