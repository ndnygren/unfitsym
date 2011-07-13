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
#ifndef NN_NEGNODE_H
#define NN_NEGNODE_H

#include "eqnNode.h"

class negNode : public eqnNode
{
	protected:
	eqnNode* right;

	public:
	virtual bool eq(eqnNode* input) const
	{
		if (type() != input->type())
			{ return false; }

		return getR()->eq(((negNode*)input)->getR());
	}

	virtual int size() const
	{
		return getR()->size();
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

	virtual std::string str() const
	{
		return "-" + right->str();
	}

	virtual eqnNode* copy() const
	{
		return new negNode(right);
	}

	virtual int type() const
	{
		return nodeTypes::neg;
	}

	negNode(eqnNode* input)
	{
		right = input->copy();
	}

	eqnNode* getR() const { return right; }
};


#endif
