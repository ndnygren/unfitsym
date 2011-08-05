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

#include "alterExpression.h"
#include <string>

using namespace std;

vector<eqnNode*> alterExpression::getAssocVector(binOpNode* input)
{
	vector<eqnNode*> outlist;
	vector<eqnNode*> stack;
	eqnNode* current;
	
	stack.push_back(input);

	while (!stack.empty())
	{
		current = stack.back();
		stack.pop_back();

		if (current->type() == input->type())
		{
			stack.push_back(((binOpNode*)current)->getL());
			stack.push_back(((binOpNode*)current)->getR());
		}
		else
		{
			outlist.push_back(current->copy());
		}
	}
	
	return outlist;
}

eqnNode* alterExpression::buildProduct(vector<eqnNode*>& list)
{
	eqnNode *temp = 0;
	eqnNode *backexpr = 0;
	unsigned int i;

	for (i = 0; i < list.size(); i++)
	{
		if (i == 0) { temp = list[i]->copy(); }
		else
		{
			backexpr = temp;
			temp = new prodNode(temp, list[i]);
			delete backexpr;
		}
	}
	return temp;
}

eqnNode* alterExpression::buildSum(vector<eqnNode*>& list)
{
	eqnNode *temp = 0;
	eqnNode *backexpr = 0;
	unsigned int i;

	for (i = 0; i < list.size(); i++)
	{
		if (i == 0) { temp = list[i]->copy(); }
		else
		{
			backexpr = temp;
			temp = new sumNode(temp, list[i]);
			delete backexpr;
		}
	}
	return temp;
}

eqnNode* alterExpression::collapse(eqnNode* input)
{
	eqnNode *ltemp, *rtemp;
	eqnNode *returnvalue = 0;

	if (input->type() == nodeTypes::sum
		|| input->type() == nodeTypes::sub
		|| input->type() == nodeTypes::prod
		|| input->type() == nodeTypes::frac
		|| input->type() == nodeTypes::hat)
	{
		ltemp = collapse(((binOpNode*)input)->getL());
		rtemp = collapse(((binOpNode*)input)->getR());
		if (ltemp->type() == nodeTypes::num && rtemp->type() == nodeTypes::num)
		{
			if (input->type() == nodeTypes::sum)
				{returnvalue = new numNode((int)(ltemp->value() + rtemp->value()));}
			else if (input->type() == nodeTypes::sub)
				{returnvalue = new numNode((int)(ltemp->value() - rtemp->value()));}
			else if (input->type() == nodeTypes::prod)
				{returnvalue = new numNode((int)(ltemp->value() * rtemp->value()));}
			else if (input->type() == nodeTypes::hat && rtemp->value() >= 0)
				{returnvalue = new numNode((int)pow(ltemp->value(), rtemp->value()));}
			else if (input->type() == nodeTypes::hat)
				{returnvalue = new hatNode(ltemp, rtemp);}
			else if (input->type() == nodeTypes::frac)
				{returnvalue = new fracNode(ltemp,rtemp);}
		}
		else
		{
			if (input->type() == nodeTypes::sum)
				{returnvalue = new sumNode(ltemp, rtemp);}
			else if (input->type() == nodeTypes::sub)
				{returnvalue = new subNode(ltemp, rtemp);}
			else if (input->type() == nodeTypes::prod)
				{returnvalue = new prodNode(ltemp, rtemp);}
			else if (input->type() == nodeTypes::hat)
				{returnvalue = new hatNode(ltemp, rtemp);}
			else if (input->type() == nodeTypes::frac)
				{returnvalue = new fracNode(ltemp,rtemp);}
		}

		delete rtemp;
		delete ltemp;

		return returnvalue;
	}
	else if (input->type() == nodeTypes::neg)
	{
		rtemp = collapse(((monoOpNode*)input)->getR());
		if (rtemp->type() == nodeTypes::num)
		{
			returnvalue = new numNode(-1 * (int)(rtemp->value()));
			delete rtemp;
			return returnvalue;
		}
		else
		{
			returnvalue = new negNode(rtemp);
			delete rtemp;
			return returnvalue;
		}
	}

	return input->copy();
}

void alterExpression::pushToBrk(vector<pair<eqnNode*,vector<eqnNode*> > >& brklist, eqnNode* base, eqnNode* arg)
{
	unsigned int i;
	
	for (i = 0; i < brklist.size(); i++)
	{
		if (brklist[i].first->eq(base))
		{
			brklist[i].second.push_back(arg);
			return;
		}
	}
	brklist.push_back(pair<eqnNode*,vector<eqnNode*> >(base, vector<eqnNode*>()));
	brklist.back().second.push_back(arg);
}

eqnNode* alterExpression::sumSimplify(sumNode* input)
{
	unsigned int i;
	vector<eqnNode*> inlist = getAssocVector(input);
	vector<pair<eqnNode*,vector<eqnNode*> > > brklist;
	numNode one(1);
	numNode negone(-1);
	prodNode *prodspare;
	negNode *negspare;
	eqnNode *outexpr, *temp3expr, *temp2expr, *tempexpr;

	for (i = 0; i < inlist.size(); i++)
	{
		if (inlist[i]->isConst())
		{
			pushToBrk(brklist, &one, inlist[i]);
		}
		else if (inlist[i]->type() == nodeTypes::prod && ((prodNode*)inlist[i])->getR()->isConst())
		{
			prodspare = ((prodNode*)inlist[i]);
			pushToBrk(brklist, prodspare->getL(), prodspare->getR());
		}
		else if (inlist[i]->type() == nodeTypes::prod && ((prodNode*)inlist[i])->getL()->isConst())
		{
			prodspare = ((prodNode*)inlist[i]);
			pushToBrk(brklist, prodspare->getR(), prodspare->getL());
		}
		else if (inlist[i]->type() == nodeTypes::neg)
		{
			negspare = ((negNode*)inlist[i]);
			pushToBrk(brklist, negspare->getR(), &negone);
		}
		else
		{
			pushToBrk(brklist, inlist[i], &one);
		}	
	}


	outexpr = 0;
	for (i = 0; i < brklist.size(); i++)
	{
		tempexpr = buildSum(brklist[i].second);
		prodspare = new prodNode(tempexpr,brklist[i].first);
		temp2expr = collapse(prodspare);

		if (outexpr == 0)
			{ outexpr = temp2expr; }
		else
		{
			temp3expr = new sumNode(outexpr, temp2expr);
			delete outexpr;
			delete temp2expr;
			outexpr = temp3expr;
		}

		delete prodspare;
		delete tempexpr;
	}

	for (i = 0; i < inlist.size(); i++)
		{ delete inlist[i]; }
	inlist.clear();

	return outexpr;
}


eqnNode* alterExpression::prodSimplify(prodNode* input)
{
	unsigned int i;
	vector<eqnNode*> inlist = getAssocVector(input);
	vector<pair<eqnNode*,vector<eqnNode*> > > brklist;
	numNode one(1);
	numNode negone(-1);
	hatNode *hatspare;
	negNode *negspare;
	eqnNode *outexpr, *temp3expr, *temp2expr, *tempexpr;

	for (i = 0; i < inlist.size(); i++)
	{
		if (inlist[i]->isConst())
		{
			pushToBrk(brklist, inlist[i], &one);
		}
		else if (inlist[i]->type() == nodeTypes::hat)
		{
			hatspare = ((hatNode*)inlist[i]);
			pushToBrk(brklist, hatspare->getL(), hatspare->getR());
		}
		else if (inlist[i]->type() == nodeTypes::neg)
		{
			negspare = ((negNode*)inlist[i]);
			pushToBrk(brklist, negspare->getR(), &one);
			pushToBrk(brklist, &negone, &one);
		}
		else
		{
			pushToBrk(brklist, inlist[i], &one);
		}	
	}


	outexpr = 0;
	for (i = 0; i < brklist.size(); i++)
	{
		tempexpr = buildSum(brklist[i].second);
		hatspare = new hatNode(brklist[i].first, tempexpr);
		temp2expr = collapse(hatspare);

		if (outexpr == 0)
			{ outexpr = temp2expr; }
		else
		{
			temp3expr = new prodNode(outexpr, temp2expr);
			delete outexpr;
			delete temp2expr;
			outexpr = temp3expr;
		}

		delete hatspare;
		delete tempexpr;
	}

	for (i = 0; i < inlist.size(); i++)
		{ delete inlist[i]; }
	inlist.clear();

	return outexpr;
}
