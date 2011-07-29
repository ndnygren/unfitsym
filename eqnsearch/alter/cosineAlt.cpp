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

#include "cosineAlt.h"

using namespace std;

vector<eqnNode*> cosineCand(cosineNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	numNode two(2);
	numNode negone(-1);
	varNode pi("\\pi");
	cosineNode *spare;
	prodNode *prodspare;
	sumNode *sumspare;
	subNode *subspare;

	prodspare = new prodNode(&two, &pi);
	sumspare = new sumNode(input->getR(), prodspare);
	subspare = new subNode(input->getR(), prodspare);
	changes.push_back(new cosineNode(sumspare));
	changes.push_back(new cosineNode(subspare));
	delete sumspare;
	delete subspare;
	delete prodspare;

	// check for int*pi
	if (input->getR()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)(input->getR());
		if (prodspare->getR()->isVar("\\pi") 
			&& prodspare->getL()->type() == nodeTypes::num)
		{
			changes.push_back(new hatNode(&negone, prodspare->getL()));
		}
	}

	//remove a pi
	if (input->getR()->type() == nodeTypes::sum)
	{
		sumspare = (sumNode*)(input->getR());
		if (sumspare->getR()->isVar("\\pi"))
		{
			spare = new cosineNode(sumspare->getL());
			changes.push_back(new negNode(spare));
			delete spare;
		}
	}

	//remove a pi
	if (input->getR()->type() == nodeTypes::sub)
	{
		subspare = (subNode*)(input->getR());
		if (subspare->getR()->isVar("\\pi"))
		{
			spare = new cosineNode(subspare->getL());
			changes.push_back(new negNode(spare));
			delete spare;
		}
	}

	//recurse 
	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		changes.push_back(new cosineNode(subchanges[i]));
	}
	freeCand(subchanges);
	subchanges.clear();

	return changes;
}
