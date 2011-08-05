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

using namespace std;

vector<eqnNode*> alterExpression::sumCand(sumNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	numNode one(1);
	numNode two(2);
	sumNode *spare, *otherspare;
	subNode *subspare;
	fracNode *fracspare;
	prodNode *prodspare, *otherprodspare;
	negNode* negspare;

	//commute
	changes.push_back(new sumNode(input->getR(), input->getL()));

	//rapid simplification
	changes.push_back(sumSimplify(input));
	

	//associate one way
	if (input->getL()->type() == nodeTypes::sum) 
	{
		spare = (sumNode*)(input->getL());
		otherspare = new sumNode(spare->getR() ,input->getR());
		changes.push_back(new sumNode(spare->getL(), otherspare));
		delete otherspare;
	}

	//associate the other way
	if (input->getR()->type() == nodeTypes::sum) 
	{
		spare = (sumNode*)(input->getR());
		otherspare = new sumNode(input->getL(), spare->getL());
		changes.push_back(new sumNode(otherspare, spare->getR()));
		delete otherspare;
	}

	// attempt to evaluate
	if ((input->getL()->type() == nodeTypes::num) 
		&& (input->getR()->type() == nodeTypes::num))
	{
		changes.push_back(new numNode(
			((numNode*)(input->getL()))->get()
			+((numNode*)(input->getR()))->get()
		));
	}


	//check left identity
	if ((input->getL()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getL()))->get() == 0)
	{
		changes.push_back(input->getR()->copy());
	}

	//check right identity
	if ((input->getR()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getR()))->get() == 0)
	{
		changes.push_back(input->getL()->copy());
	}


	//recursing
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new sumNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new sumNode(input->getL(), subchanges[i]);
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();


	//handle frac
	if (input->getR()->type() == nodeTypes::frac) 
	{
		fracspare = (fracNode*)(input->getR());
		prodspare = new prodNode(fracspare->getR(), input->getL());
		spare = new sumNode(prodspare, fracspare->getL());
		changes.push_back(new fracNode(spare, fracspare->getR()));
		delete spare;
		delete prodspare;
	}

	// reverse distribute
	if (input->getL()->type() == nodeTypes::prod
		&& input->getR()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)(input->getL());
		otherprodspare = (prodNode*)(input->getR());
		if (prodspare->getR()->eq(otherprodspare->getR()))
		{
			spare = new sumNode(prodspare->getL(),otherprodspare->getL());
			changes.push_back(new prodNode(spare, prodspare->getR()));
			delete spare;
		}
	}

	//commute with right subtraction
	if (input->getR()->type() == nodeTypes::sub)
	{
		subspare = new subNode(input->getL(), ((subNode*)(input->getR()))->getR());
		changes.push_back(new sumNode( ((subNode*)(input->getR()))->getL(), subspare));
		delete subspare;
	}

	//create right subtraction
	if (input->getR()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)(input->getR());
		if (prodspare->getL()->type() == nodeTypes::num && 
			((numNode*)(prodspare->getL()))->get() == -1)
		{
			subspare = new subNode(input->getL(), prodspare->getR());
			changes.push_back(subspare);
		}
	}

	//handle neg
	if (input->getR()->type() == nodeTypes::neg)
	{
		negspare = (negNode*)(input->getR());
		changes.push_back(new subNode(input->getL(),negspare->getR()));
	}

	//check	for same base
	if (input->getL()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)(input->getL());
		if (prodspare->getR()->eq(input->getR()))
		{
			spare = new sumNode(prodspare->getL(),&one);
			changes.push_back(new prodNode(spare,input->getR()));
			delete spare;
		}
	}

	// check double
	if (input->getR()->eq(input->getL()))
	{
		changes.push_back(new prodNode(&two,input->getR()));
	}

	return changes;
}
