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

#include "fracAlt.h"

using namespace std;

vector<eqnNode*> fracCand(fracNode* input)
{
	unsigned int i;
	nodeTypes types;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	numNode one(1);
	fracNode *spare, *otherspare;
	prodNode *prodspare;

	//separate
	otherspare = new fracNode(&one, input->getR());
	changes.push_back(new prodNode(input->getL(), otherspare));
	delete otherspare;

	//flip denominator up
	if (input->getR()->type() == types.frac) 
	{
		spare = (fracNode*)(input->getR());
		otherspare = new fracNode(spare->getR() ,spare->getL());
		changes.push_back(new prodNode(input->getL(), otherspare));
		delete otherspare;
	}

	//numerator fraction down
	if (input->getL()->type() == types.frac) 
	{
		spare = (fracNode*)(input->getL());
		prodspare = new prodNode(spare->getR(), input->getR());
		changes.push_back(new fracNode(spare->getL(), prodspare));
		delete prodspare;
	}

	// attempt to evaluate (exact integers only)
	if ((input->getL()->type() == types.num) 
		&& (input->getR()->type() == types.num)
		&& ( ((numNode*)(input->getL()))->get()
			% ((numNode*)(input->getR()))->get() == 0))
	{
		changes.push_back(new numNode(
			((numNode*)(input->getL()))->get()
			/((numNode*)(input->getR()))->get()
		));
	}

	//recurse left
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new fracNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//recurse right 
	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new fracNode(input->getL(), subchanges[i]);
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	//check right identity
	if ((input->getR()->type() == types.num) 
		&& ((numNode*)(input->getR()))->get() == 1)
	{
		changes.push_back(input->getL()->copy());
	}

	//handle zero
	if ((input->getL()->type() == types.num) 
		&& ((numNode*)(input->getL()))->get() == 0)
	{
		changes.push_back(new numNode(0));
	}

	return changes;
}