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
#ifndef NN_INTBNODE_H
#define NN_INTBNODE_H

#include "intNode.h"

/**
 * @class intBNode 
 * 
 * @brief Parse tree node representing the definite integral of the left subtree,
 * 	with respect to the variable in the right subtree.
 * 
 */

class intBNode : public intNode
{
	protected:
	/**
	 * @brief the expression representing the upper bound of the integral
	 */
	eqnNode* upper;

	/**
	 * @brief the expression representing the upper bound of the integral
	 */
	eqnNode* lower;

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
		if (upper != 0)
		{
			delete upper;
			upper = 0;
		}
		if (lower != 0)
		{
			delete lower;
			lower = 0;
		}
	}

	public:
	virtual eqnNode* copy() const 
		{ return new intBNode(getL(), getR(), getUpper(), getLower()); } 

	virtual int type() const { return nodeTypes::integralb; } 

	virtual std::string str() const
	{
		return "\\int_{"+ getLower()->str() + "}^{" + getUpper()->str() + "} " + left->str() + " d{" + right->str()+ "}";
	}

	virtual std::string nice_str() const
	{
		return "\\int_{"+ getLower()->nice_str() + "}^{" + getUpper()->nice_str() + "} " + left->nice_str() + " d{" + right->nice_str()+ "}";
	}


	/**
	 * @brief standard getter function for upper bound
	 * @returns upper bound expression
	 */
	virtual eqnNode* getUpper() const {return upper;}

	/**
	 * @brief standard getter function for lower bound
	 * @returns lower bound expression
	 */
	virtual eqnNode* getLower() const {return lower;}

	virtual eqnNode* collapse() const
	{
		eqnNode* ltemp = left->collapse();
		eqnNode* outexpr;
		
		outexpr = new intBNode(ltemp, getR(), getUpper(), getLower());
		delete ltemp;

		return outexpr;
	}

	intBNode(eqnNode* lin, eqnNode* rin, eqnNode* upin, eqnNode* lowin) : intNode(lin,rin)
	{
		upper = upin->copy();
		lower = lowin->copy();
	}
	virtual ~intBNode() { deleteAll(); }

	virtual eqnNode* new_node(eqnNode* linput, eqnNode* rinput) const
	{
		return new intBNode(linput, rinput, getUpper(), getLower());
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

		if (getUpper()->tNum() == index)
		{
				delete getUpper();
				upper = expr->copy();
		}
		else
		{
			getUpper()->replace(index,expr);
		}
		if (getLower()->tNum() == index)
		{
				delete getLower();
				lower = expr->copy();
		}
		else
		{
			getLower()->replace(index,expr);
		}
	}

	virtual std::pair<bool,std::vector<std::pair<int, eqnNode*> > > compareTemplate(eqnNode* texpr) const
	{
		unsigned int i;

		std::pair<bool, std::vector<std::pair<int, eqnNode*> > > lpair; 
		std::pair<bool, std::vector<std::pair<int, eqnNode*> > > rpair; 
		std::pair<bool, std::vector<std::pair<int, eqnNode*> > > upair; 
		std::pair<bool, std::vector<std::pair<int, eqnNode*> > > lowpair; 
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
			upair = getUpper()->compareTemplate(((intBNode*)texpr)->getUpper());
			lowpair = getLower()->compareTemplate(((intBNode*)texpr)->getLower());
			if (!lpair.first || !rpair.first ||
				!upair.first || !lowpair.first)
			{
				retpair.first = false;

				for (i = 0; i < lpair.second.size(); i++)
					{ delete lpair.second[i].second; }
				for (i = 0; i < rpair.second.size(); i++)
					{ delete rpair.second[i].second; }
				for (i = 0; i < upair.second.size(); i++)
					{ delete upair.second[i].second; }
				for (i = 0; i < lowpair.second.size(); i++)
					{ delete lowpair.second[i].second; }

				return retpair;
			}
			else
			{
				retpair.first = true;

				for (i = 0; i < lpair.second.size(); i++)
					{ retpair.second.push_back(lpair.second[i]); }
				for (i = 0; i < rpair.second.size(); i++)
					{ retpair.second.push_back(rpair.second[i]); }
				for (i = 0; i < upair.second.size(); i++)
					{ retpair.second.push_back(upair.second[i]); }
				for (i = 0; i < lowpair.second.size(); i++)
					{ retpair.second.push_back(lowpair.second[i]); }
				
				return retpair;
			}
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
};


#endif
