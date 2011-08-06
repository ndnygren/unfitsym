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

vector<eqnNode*> alterExpression::prodCand(prodNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	numNode one(1);
	numNode two(2);
	prodNode *spare, *otherspare;
	fracNode *fracspare; 
	sumNode *sumspare; 
	subNode *subspare; 
	prodNode *prodspare; 
	hatNode *hat1spare, *hat2spare; 
	negNode *negspare;

	//commute
	changes.push_back(new prodNode(input->getR(), input->getL()));

	//rapid simplification
	changes.push_back(prodSimplify(input));

	//associate one way
	if (input->getL()->type() == nodeTypes::prod) 
	{
		spare = (prodNode*)(input->getL());
		otherspare = new prodNode(spare->getR() ,input->getR());
		changes.push_back(new prodNode(spare->getL(), otherspare));
		delete otherspare;
	}

	//associate the other way
	if (input->getR()->type() == nodeTypes::prod) 
	{
		spare = (prodNode*)(input->getR());
		otherspare = new prodNode(input->getL(), spare->getL());
		changes.push_back(new prodNode(otherspare, spare->getR()));
		delete otherspare;
	}

	// attempt to evaluate
	if ((input->getL()->type() == nodeTypes::num) 
		&& (input->getR()->type() == nodeTypes::num))
	{
		changes.push_back(new numNode(
			((numNode*)(input->getL()))->get()
			*((numNode*)(input->getR()))->get()
		));
	}


	//recurse left
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new prodNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//recurse right 
	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new prodNode(input->getL(), subchanges[i]);
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//check left identity
	if ((input->getL()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getL()))->get() == 1)
	{
		changes.push_back(input->getR()->copy());
	}

	//check right identity
	if ((input->getR()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getR()))->get() == 1)
	{
		changes.push_back(input->getL()->copy());
	}

	//create neg
	if ((input->getL()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getL()))->get() == -1)
	{
		changes.push_back(new negNode(input->getR()));
	}

	//handle zero
	if ((input->getR()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getR()))->get() == 0)
	{
		changes.push_back(new numNode(0));
	}

	//handle frac
	if (input->getR()->type() == nodeTypes::frac) 
	{
		fracspare = (fracNode*)(input->getR());
		otherspare = new prodNode(input->getL(),fracspare->getL());
		changes.push_back(new fracNode(otherspare, fracspare->getR()));
		delete otherspare;
	}

	//distribute over addition
	if (input->getR()->type() == nodeTypes::sum) 
	{
		sumspare = (sumNode*)(input->getR());
		spare = new prodNode(input->getL(), sumspare->getR());
		otherspare = new prodNode(input->getL(), sumspare->getL());
		changes.push_back(new sumNode(spare, otherspare));
		delete otherspare;
		delete spare;
	}
	
	//distribute over subtraction
	if (input->getR()->type() == nodeTypes::sub)
	{
		subspare = (subNode*)(input->getR());
		spare = new prodNode(input->getL(), subspare->getL());
		otherspare = new prodNode(input->getL(), subspare->getR());
		changes.push_back(new subNode(spare, otherspare));
		delete otherspare;
		delete spare;
	}

	//handle same exp bases
	if (input->getL()->type() == nodeTypes::hat
		&& input->getR()->type() == nodeTypes::hat)
	{
		hat1spare = (hatNode*)(input->getL());
		hat2spare = (hatNode*)(input->getR());
	
		if (hat1spare->getL()->eq(hat2spare->getL()))
		{
			sumspare = new sumNode(hat1spare->getR(), hat2spare->getR());	
			changes.push_back(new hatNode(hat1spare->getL(), sumspare));
			delete sumspare;
		}
	}

	//handle same exp bases(one side non-hat)
	if (input->getL()->type() == nodeTypes::hat)
	{
		hat1spare = (hatNode*)(input->getL());
		if (hat1spare->getL()->eq(input->getR()))
		{
			sumspare = new sumNode(hat1spare->getR(), &one);
			changes.push_back(new hatNode(hat1spare->getL(), sumspare));
			delete sumspare;
		}
	}

	//handle same exp bases(one side no-hats)
	if (input->getL()->eq(input->getR()))
	{
		changes.push_back(new hatNode(input->getL(), &two));
	}

	//handle same exp
	if (input->getL()->type() == nodeTypes::hat
		&& input->getR()->type() == nodeTypes::hat)
	{
		hat1spare = (hatNode*)(input->getL());
		hat2spare = (hatNode*)(input->getR());
	
		if (hat1spare->getR()->eq(hat2spare->getR()))
		{
			prodspare = new prodNode(hat1spare->getL(), hat2spare->getL());
			
			changes.push_back(new hatNode(prodspare, hat1spare->getR()));
			delete prodspare;
		}
	}
	
	if (input->getL()->type() == nodeTypes::neg)
	{
		negspare = (negNode*)(input->getL());
		spare = new prodNode(negspare->getR(),input->getR());
		changes.push_back(new negNode(spare));
		delete spare;
	}

	return changes;
}
