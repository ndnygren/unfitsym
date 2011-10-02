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
#ifndef NN_LNNODE_H
#define NN_LNNODE_H

#include "monoOpNode.h"

/**
 * @class lnNode
 *
 * @brief Monic operator, representing the natural log node
 */
class lnNode : public monoOpNode
{
	public:
	virtual std::string str() const { return "\\ln(" + right->str() + ")"; }
	virtual std::string nice_str() const { return "\\ln(" + right->nice_str() + ")"; }
	virtual eqnNode* copy() const { return new lnNode(right); }
	virtual int type() const { return nodeTypes::ln; }
	lnNode(eqnNode* input) { right = input->copy(); }

	virtual double value() const 
	{ 
		double arg = getR()->value();
		if (arg > 0)
			{ return log(arg); }
		else
			{ return 0; }
	}

	virtual ~lnNode() { deleteAll(); }
	virtual eqnNode* new_node(eqnNode* input) const { return new lnNode(input); }
};


#endif
