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

#include "subAlt.h"

using namespace std;

vector<eqnNode*> subCand(subNode* input)
{
	unsigned int i;
	numNode one(1);
	numNode negone(-1);
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	subNode *spare;
	sumNode *sumspare;
	prodNode *prodspare;
	negNode *negspare;

	// attempt to evaluate
	if ((input->getL()->type() == nodeTypes::num) 
		&& (input->getR()->type() == nodeTypes::num))
	{
		changes.push_back(new numNode(
			((numNode*)(input->getL()))->get()
			-((numNode*)(input->getR()))->get()
		));
	}

	//recurse left
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new subNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//recurse right 
	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new subNode(input->getL(), subchanges[i]);
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	// reduce to zero
	if (input->getL()->eq(input->getR()))
	{
		changes.push_back(new numNode(0));
	}

	// replace with addition
	prodspare = new prodNode(&negone, input->getR());
	changes.push_back(new sumNode(input->getL(), prodspare));
	delete prodspare;

	// replace with addition alternate
	negspare = new negNode(input->getR());
	changes.push_back(new sumNode(input->getL(), negspare));
	delete negspare;

	//distribute left over addition
	if (input->getL()->type() == nodeTypes::sum) 
	{
		sumspare = (sumNode*)(input->getL());
		spare = new subNode(sumspare->getR(), input->getR());
		changes.push_back(new sumNode(sumspare->getL(), spare));
		delete spare;
	}

	//distribute right over addition
	if (input->getR()->type() == nodeTypes::sum) 
	{
		sumspare = (sumNode*)(input->getR());
		spare = new subNode(input->getL(), sumspare->getL());
		changes.push_back(new subNode(spare, sumspare->getR()));
		delete spare;
	}

	//check	for same base
	if (input->getL()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)(input->getL());
		if (prodspare->getR()->eq(input->getR()))
		{
			sumspare = new sumNode(prodspare->getL(),&negone);
			changes.push_back(new prodNode(sumspare,input->getR()));
			delete sumspare;
		}
	}

	return changes;
}
