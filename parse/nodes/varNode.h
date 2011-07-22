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
#ifndef NN_VARNODE_H
#define NN_VARNODE_H

#include "leafNode.h"
#include <string>

/*
 * class varNode
 *
 * Terminal parse tree node represting a variable in the equation. The parser
 *	will only accept single lower case letters for variable, this is by
 *	choice. The structure allows for strings of arbitrary length and will
 *	also be used for LaTeX syntax greek ("\pi","\phi",...)
 */

class varNode : public leafNode
{
	protected:
	std::string name;

	public:
	virtual bool eq(eqnNode* input) const
	{
		if (type() != input->type())
			{ return false; }

		return (get() == (((varNode*)input)->get()));
	}

	virtual eqnNode* copy() const { return new varNode(get()); }
	virtual int type() const { return nodeTypes::var; }
	std::string get() const { return name; }
	virtual std::string str() const { return name; }

	varNode(std::string input) { name = input; }

	/*
	 * bool isConst()
	 *
	 * returns false since this expression does contain a variable
	 * 
	 */
	virtual bool isConst() const
		{ return false; }

	/*
	 * bool isConst(std::string name)
	 *
	 * returns true iff the expression does not contain the 
	 *	specified variable
	 * 
	 */
	virtual bool isConst(const std::string& name) const
		{ return !(get() == name); }
};


#endif
