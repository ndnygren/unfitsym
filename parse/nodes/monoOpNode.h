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

/**
 * @class monoOpNode
 *
 * @brief Pure virutal interface for Monic operators such as -(),sin(), ...etc.
 */
class monoOpNode : public eqnNode
{
	protected:
	/**
	 * @brief the subtree of the monic operator
	 * @details The name 'right' is chosen for consistency with binOpNode.
	 * There is only one subtree in a monic operator.
	 */
	eqnNode* right; 

	virtual void deleteAll() 
	{
		if (right != 0)
		{
			delete right;
			right = 0;
		}
	}

	public:
	virtual bool eq(const eqnNode* input) const
	{
		if (type() != input->type())
			{ return false; }

		return getR()->eq(((monoOpNode*)input)->getR());
	}


	virtual int size() const
	{
		return getR()->size() + 1;
	}



	/**
	 * @brief Allows access to the subtree
	 * @returns the subtree in eqnNode* form
	 */
	eqnNode* getR() const { return right; }

	/*
	 * bool isConst()
	 *
	 * returns true iff the expression contains no variables
	 * 
	 */
	virtual bool isConst() const
		{ return getR()->isConst(); }

	virtual bool isMono() const { return true; }

	virtual eqnNode* collapse() const { return copy(); }

	/*
	 * bool isConst(std::string name)
	 *
	 * returns true iff the expression does not contain the 
	 *	specified variable
	 * 
	 */
	virtual bool isConst(const std::string& name) const
		{ return getR()->isConst(name); }

	virtual bool isTemplate() const { return getR()->isTemplate(); }

	virtual void replace(const std::string& var, eqnNode* expr)
	{
		if (getR()->isVar(var))
		{
			delete getR();
			right = expr->copy();
		}
		else
		{
			getR()->replace(var,expr);
		}
	}

	virtual void replace(int index, eqnNode* expr)
	{
		if (getR()->type() == nodeTypes::tvar)
		{
			if (getR()->tNum() == index)
			{
				delete getR();
				right = expr->copy();
			}
		}
		else
		{
			getR()->replace(index,expr);
		}
	}

	virtual std::pair<bool,std::vector<std::pair<int, eqnNode*> > > compareTemplate(eqnNode* texpr) const
	{
		std::pair<bool,std::vector<std::pair<int, eqnNode*> > > retpair; 

		if (eq(texpr))
		{ 
			retpair.first = true;
			return retpair;
		}
		else if (texpr->type() == type())
		{
			return getR()->compareTemplate(((monoOpNode*)texpr)->getR());
		}
		else if (texpr->type() == nodeTypes::tvar)
		{
			retpair.first = true;
			retpair.second.push_back(std::pair<int,eqnNode*>(texpr->tNum(), copy()));
			return retpair;
		}
		else
		{
			retpair.first = false;
			return retpair;
		}
	}

	virtual eqnNode* new_node(eqnNode* input) const = 0;
};


#endif
