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

#include "derivAlt.h"

using namespace std;

vector<eqnNode*> derivCand(derivNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	derivNode *spare, *otherspare;
	sumNode *sumspare;
	prodNode *prodspare, *prod1spare, *prod2spare;

	//check for int 
	if (input->getL()->type() == nodeTypes::num) 
	{
		changes.push_back(new numNode(0));
	}

	//check equality
	if (input->getL()->eq(input->getR()))
	{
		changes.push_back(new numNode(1));
	}

	// sum rule
	if (input->getL()->type() == nodeTypes::sum) 
	{
		sumspare = (sumNode*)(input->getL());
		spare = new derivNode(sumspare->getL(), input->getR());
		otherspare = new derivNode(sumspare->getR(), input->getR());
		changes.push_back(new sumNode(spare,otherspare));
		delete spare;
		delete otherspare;
	}

	//product rule
	if (input->getL()->type() == nodeTypes::prod) 
	{
		prodspare = (prodNode*)(input->getL());
		spare = new derivNode(prodspare->getL(), input->getR());
		otherspare = new derivNode(prodspare->getR(), input->getR());
		prod1spare = new prodNode(spare, prodspare->getR());
		prod2spare = new prodNode(otherspare, prodspare->getL());
		changes.push_back(new sumNode(prod1spare,prod2spare));
		delete spare;
		delete otherspare;
		delete prod1spare;
		delete prod2spare;
	}

	//recursing
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new derivNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();


	return changes;
}
