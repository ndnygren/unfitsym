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
#ifndef NN_SINENODE_H
#define NN_SINENODE_H

#include "monoOpNode.h"

/**
 * @class sineNode
 *
 * @brief Monic operator, representing the sine function
 */
class sineNode : public monoOpNode
{
	public:
	virtual std::string str() const { return "\\sin(" + right->str() + ")"; }
	virtual std::string nice_str() const { return "\\sin(" + right->nice_str() + ")"; }
	virtual eqnNode* copy() const { return new sineNode(right); }
	virtual int type() const { return nodeTypes::sin; }
	sineNode(eqnNode* input) { right = input->copy(); }
	virtual double value() const { return sin(getR()->value()); }
	virtual ~sineNode() { deleteAll(); }
	virtual eqnNode* new_node(eqnNode* input) const { return new sineNode(input); }
};


#endif
