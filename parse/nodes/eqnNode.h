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
#include <string>

class eqnNode
{
	protected:
	nodeTypes types;
	public:
	virtual void deleteAll() { };
	virtual eqnNode* copy() const = 0;
	virtual bool eq(eqnNode* input) const = 0;
	virtual int size() const = 0;
	virtual int type() const = 0;
	virtual bool isLeaf() const { return false; }
	virtual std::string str() const { return "tree data"; }
	virtual ~eqnNode() { }
};


#endif
