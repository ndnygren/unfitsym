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
#include "monoOpNode.h"

/**
 * @class binOpNode 
 * 
 * @brief virtual class describing parse tree nodes for binary operators.
 * (ex. addition, subtraction). Handles memory allocation details.
 * 
 * 
 */

class binOpNode : public eqnNode
{
	protected:
	/**
	 * @brief the left subtree of the binary operator
	 */
	eqnNode* left;

	/**
	 * @brief the right subtree of the binary operator
	 */
	eqnNode* right;

	/*
	 * virtual void deleteAll() 
	 * 
	 * Recursively handles the deallocation of memory for the parse tree
	 */
	virtual void deleteAll() 
	{
		if (left != 0)
		{
			delete left;
			left = 0;
		}
		if (right != 0)
		{
			delete right;
			right = 0;
		}
	}

	public:
	// int max(int left, int right) const
	/**
 	 * @brief usual max function for integers
	 * @returns the largest of {left,right}
	 * 
	 */
	static int max(int left, int right)
	{
		if (left < right) { return right; }
		return left;
	}

	virtual bool eq(const eqnNode* input) const
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


	// getL() 
	/**
	 * @brief Allows traversal of the left subtree
	 * @returns the left eqnNode* subtree
	 */
	eqnNode* getL() const { return left; }

	// getR() returns the right subtree
	/**
	 * @brief Allows traversal of the right subtree
	 * @returns the right eqnNode* subtree
	 */
	eqnNode* getR() const { return right; }

	virtual bool isConst() const
		{ return getL()->isConst() && getR()->isConst(); }

	virtual bool isBin() const { return true; }

	/*
	 * bool isConst(std::string name)
	 *
	 * returns true iff the expression does not contain the 
	 *	specified variable
	 * 
	 */
	virtual bool isConst(const std::string& name) const
		{ return getL()->isConst(name) && getR()->isConst(name); }

	virtual bool isTemplate() const { return getL()->isTemplate() || getR()->isTemplate(); }

	virtual void replace(const std::string& var, eqnNode* expr)
	{
		if (getL()->isVar(var))
		{
			delete getL();
			left = expr->copy();
		}
		else
		{
			getL()->replace(var,expr);
		}
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
		monoOpNode* temp;

		if (getL()->type() == nodeTypes::tvar)
		{
			temp = (monoOpNode*)getL();
			if (((numNode*)temp->getR())->get() == index)
			{
				delete getL();
				left = expr->copy();
			}
		}
		else
		{
			getL()->replace(index,expr);
		}
	
		if (getR()->type() == nodeTypes::tvar)
		{
			temp = (monoOpNode*)getR();
			if (((numNode*)temp->getR())->get() == index)
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
		unsigned int i;

		std::pair<bool, std::vector<std::pair<int, eqnNode*> > > lpair; 
		std::pair<bool, std::vector<std::pair<int, eqnNode*> > > rpair; 
		std::pair<bool, std::vector<std::pair<int, eqnNode*> > > retpair; 

		if (eq(texpr))
		{ 
			retpair.first = true;
			return retpair;
		}
		else if (texpr->type() == type())
		{
			lpair = getL()->compareTemplate(((binOpNode*)texpr)->getL());
			rpair = getR()->compareTemplate(((binOpNode*)texpr)->getR());
			if (!lpair.first || !rpair.first)
			{
				retpair.first = false;

				for (i = 0; i < lpair.second.size(); i++)
					{ delete lpair.second[i].second; }
				for (i = 0; i < rpair.second.size(); i++)
					{ delete rpair.second[i].second; }

				return retpair;
			}
			else
			{
				retpair.first = true;

				for (i = 0; i < lpair.second.size(); i++)
					{ retpair.second.push_back(lpair.second[i]); }
				for (i = 0; i < rpair.second.size(); i++)
					{ retpair.second.push_back(rpair.second[i]); }
				
				return retpair;
			}
		}
		else if (texpr->type() == nodeTypes::tvar && type() != nodeTypes::ident)
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

	/**
	 * @brief produces a new node of this node's type
	 * @param linput the left subtree of the new node
	 * @param rinput the right subtree of the new node
	 * @returns the new node of this node's type
	 */
	virtual eqnNode* new_node(eqnNode* linput, eqnNode* rinput) const = 0;
};


#endif
