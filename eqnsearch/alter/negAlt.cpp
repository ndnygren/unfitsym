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

#include "negAlt.h"

using namespace std;

vector<eqnNode*> negCand(negNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	numNode one(1);
	negNode *spare, *otherspare;
	sumNode *sumspare;

	// attempt to evaluate (exact integers only)
	if (input->getR()->type() == nodeTypes::num) 
	{
		changes.push_back(new numNode( -1 * ((numNode*)(input->getR()))->get()));
	}

	//recurse 
	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new negNode( subchanges[i]);
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//cancellation
	if (input->getR()->type() == nodeTypes::neg) 
	{
		changes.push_back(((negNode*)(input->getR()))->getR()->copy());
	}

	//distribute
	if (input->getR()->type() == nodeTypes::sum) 
	{
		sumspare = (sumNode*)(input->getR());
		spare = new negNode(sumspare->getL());
		otherspare = new negNode(sumspare->getR());
		changes.push_back(new sumNode(spare,otherspare));
		delete spare;
		delete otherspare;
	}

	// attempt to evaluate
	if (input->getR()->type() == nodeTypes::num)
	{
		changes.push_back(new numNode( -1*((numNode*)(input->getR()))->get()));
	}


	return changes;
}
