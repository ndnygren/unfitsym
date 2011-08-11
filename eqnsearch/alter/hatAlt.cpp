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

vector<eqnNode*> alterExpression::hatCand(hatNode* input)
{
	unsigned int i;
	int intspare;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	numNode one(1);
	numNode zero(0);
	hatNode *spare, *otherspare;
	sumNode *sumspare;
	prodNode *prodspare;
	negNode *negspare;
	numNode *numspare;

	//pull one out
	if (input->getR()->type() == nodeTypes::num)
	{
		intspare = ((numNode*)(input->getR()))->get();
		numspare = new numNode(intspare-1);
		spare = new hatNode(input->getL(), numspare);
		changes.push_back(new prodNode(spare, input->getL()));
		delete spare;
		delete numspare;
	}

	//handle identity
	if (input->getR()->type() == nodeTypes::num
		&& ((numNode*)(input->getR()))->get()==1) 
	{
		changes.push_back(input->getL()->copy());
	}

	//handle zero
	if (input->getR()->type() == nodeTypes::num
		&& ((numNode*)(input->getR()))->get()==0) 
	{
		changes.push_back(new numNode(1));
	}

	//handle addition
	if (input->getR()->type() == nodeTypes::sum)
	{
		sumspare = (sumNode*)(input->getR());
		spare = new hatNode(input->getL(), sumspare->getL());
		otherspare = new hatNode(input->getL(), sumspare->getR());
		changes.push_back(new prodNode(spare,otherspare));
		delete spare;
		delete otherspare;
	}

	//handle base multiplication
	if (input->getL()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)(input->getL());
		spare = new hatNode(prodspare->getL(), input->getR());
		otherspare = new hatNode(prodspare->getR(), input->getR());
		changes.push_back(new prodNode(spare,otherspare));
		delete spare;
		delete otherspare;
	}

	//handle multiplication
	if (input->getR()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)(input->getR());
		spare = new hatNode(input->getL(), prodspare->getL());
		changes.push_back(new hatNode(spare,prodspare->getR()));
		delete spare;
	}

	//handle hat chains
	if (input->getL()->type() == nodeTypes::hat)
	{
		prodspare = new prodNode(((hatNode*)input->getL())->getR(),input->getR());
		changes.push_back(new hatNode(((hatNode*)input->getL())->getL(), prodspare));
		delete prodspare;
	}

	//recurse left
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new hatNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//recurse right 
	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new hatNode(input->getL(), subchanges[i]);
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//flip
	negspare = new negNode(input->getR());
	spare = new hatNode(input->getL(), negspare);
	changes.push_back(new fracNode(&one, spare));
	delete spare;
	delete negspare;

	return changes;
}
