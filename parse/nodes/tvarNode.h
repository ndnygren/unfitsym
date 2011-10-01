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
#ifndef NN_TVARNODE_H
#define NN_TVARNODE_H

#include "monoOpNode.h"
#include "numNode.h"

/**
 * @class tvarNode
 *
 * @brief Monic operator, representing a template variable, indexed by an integer
 */
class tvarNode : public monoOpNode
{
	public:
	/**
	 * @brief the size of the negNode* tree
	 * @details this nodes size is ignored as long as it does not occur twice in a row. This will be modified in the future, when a proper metric will make this distinction.
	 */
	virtual int size() const
	{
		return 1;
	}

	virtual std::string str() const
	{
		return "TV_{" + right->str() + "}";
	}

	virtual std::string nice_str() const
	{
		return "TV_{" + right->nice_str() + "}";
	}

	virtual eqnNode* copy() const
	{
		return new tvarNode(right);
	}

	virtual eqnNode* collapse() const
	{
		return copy();
	}

	virtual bool isTemplate() const { return true; }

	virtual int type() const { return nodeTypes::tvar; }
	tvarNode(eqnNode* input) { right = input->copy(); }
	tvarNode(int input) { right = new numNode(input); }
	virtual double value() const { return 0; }
	virtual ~tvarNode() { deleteAll(); }

};


#endif
