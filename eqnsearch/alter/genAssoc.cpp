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

#include "../../parse/nodes/sumNode.h"
#include "../../parse/nodes/prodNode.h"
#include "../../parse/nodes/subNode.h"
#include "../../parse/nodes/fracNode.h"
#include "../../parse/nodes/negNode.h"
#include "../../parse/nodes/hatNode.h"

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

void alterExpression::negList(vector<eqnNode*>& list)
{
	eqnNode *temp;
	prodNode *prodspare;
	unsigned int i;
	numNode negone(-1);

	for (i = 0; i < list.size(); i++)
	{
		temp = list[i];
		if (temp->type() == nodeTypes::prod)
		{
			prodspare = (prodNode*)temp;
			if (prodspare->getL()->isConst())
			{
				temp = new negNode(prodspare->getL());
				list[i] = new prodNode(temp, prodspare->getR());
				delete temp;
				delete prodspare;
			}
			else
			{
				temp = new negNode(prodspare->getR());
				list[i] = new prodNode(temp, prodspare->getL());
				delete temp;
				delete prodspare;
			}
		}
		else
		{
			list[i] = new prodNode(&negone,temp);
			delete temp;
		}
	}
}

void alterExpression::unSub(vector<eqnNode*>& list)
{
	subNode* temp;
	numNode negone(-1);
	vector<eqnNode*> sparelist;
	unsigned int i;
	
	for (i = 0; i < list.size(); i++)
	{
		if (list[i]->type() == nodeTypes::sub)
		{
			temp = (subNode*)list[i];
			list.erase(list.begin()+i);
			i--;
			if (temp->getL()->type() == nodeTypes::sum)
			{
				sparelist = getAssocVector((binOpNode*)(temp->getL()));
				while(!sparelist.empty())
				{
					list.push_back(sparelist.back());
					sparelist.pop_back();
				}
			}
			else
			{
				list.push_back(temp->getL()->copy());
			}
			if (temp->getR()->type() == nodeTypes::sum)
			{
				sparelist = getAssocVector((binOpNode*)(temp->getR()));
				negList(sparelist);
				while(!sparelist.empty())
				{
					list.push_back(sparelist.back());
					sparelist.pop_back();
				}
			}
			else
			{
				list.push_back(new prodNode(&negone, temp->getR()));
			}
			delete temp;
		}	
	}
}

void alterExpression::invertList(vector<eqnNode*>& list)
{
	eqnNode *temp;
	hatNode *hatspare;
	unsigned int i;
	numNode negone(-1);

	for (i = 0; i < list.size(); i++)
	{
		temp = list[i];
		if (temp->type() == nodeTypes::hat)
		{
			hatspare = (hatNode*)temp;
			temp = new negNode(hatspare->getR());
			list[i] = new hatNode(hatspare->getL(), temp);
			delete temp;
			delete hatspare;
		}
		else
		{
			list[i] = new hatNode(temp, &negone);
			delete temp;
		}
	}
}

void alterExpression::unFrac(vector<eqnNode*>& list)
{
	fracNode* temp;
	numNode negone(-1);
	vector<eqnNode*> sparelist;
	unsigned int i;
	
	for (i = 0; i < list.size(); i++)
	{
		if (list[i]->type() == nodeTypes::frac)
		{
			temp = (fracNode*)list[i];
			list.erase(list.begin()+i);
			i--;
			if (temp->getL()->type() == nodeTypes::prod)
			{
				sparelist = getAssocVector((binOpNode*)(temp->getL()));
				unFrac(sparelist);
				while(!sparelist.empty())
				{
					list.push_back(sparelist.back());
					sparelist.pop_back();
				}
			}
			else
			{
				list.push_back(temp->getL()->copy());
			}
			if (temp->getR()->type() == nodeTypes::prod)
			{
				sparelist = getAssocVector((binOpNode*)(temp->getR()));
				unFrac(sparelist);
				invertList(sparelist);
				while(!sparelist.empty())
				{
					list.push_back(sparelist.back());
					sparelist.pop_back();
				}
			}
			else
			{
				list.push_back(new hatNode(temp->getR(),&negone));
			}
			delete temp;
		}	
	}
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

	unSub(inlist);

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
		temp2expr = prodspare->collapse();

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

	unFrac(inlist);

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
		temp2expr = hatspare->collapse();

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

	tempexpr = outexpr;
	outexpr = tempexpr->collapse();
	delete tempexpr;
	return outexpr;
}
