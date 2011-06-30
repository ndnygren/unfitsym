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

#include "sumAlt.h"

using namespace std;

vector<eqnNode*> sumCand(sumNode* input)
{
	unsigned int i;
	nodeTypes types;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	sumNode *spare, *otherspare;

	//commute
	changes.push_back(new sumNode(input->getR(), input->getL()));


	//associate one way
	if (input->getL()->type() == types.sum) 
	{
		spare = (sumNode*)(input->getL());
		otherspare = new sumNode(spare->getR() ,input->getR());
		changes.push_back(new sumNode(spare->getL(), otherspare));
		delete otherspare;
	}

	//associate the other way
	if (input->getR()->type() == types.sum) 
	{
		spare = (sumNode*)(input->getR());
		otherspare = new sumNode(input->getL(), spare->getL());
		changes.push_back(new sumNode(otherspare, spare->getR()));
		delete otherspare;
	}

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


	return changes;
}
