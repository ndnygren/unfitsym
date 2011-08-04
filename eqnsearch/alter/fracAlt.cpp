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

vector<eqnNode*> alterExpression::fracCand(fracNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	numNode one(1);
	fracNode *spare, *otherspare;
	prodNode *prodspare;
	hatNode *hat1spare, *hat2spare;
	negNode *negspare;

	//separate
	otherspare = new fracNode(&one, input->getR());
	changes.push_back(new prodNode(input->getL(), otherspare));
	delete otherspare;

	//flip denominator up
	if (input->getR()->type() == nodeTypes::frac) 
	{
		spare = (fracNode*)(input->getR());
		otherspare = new fracNode(spare->getR() ,spare->getL());
		changes.push_back(new prodNode(input->getL(), otherspare));
		delete otherspare;
	}

	//numerator fraction down
	if (input->getL()->type() == nodeTypes::frac) 
	{
		spare = (fracNode*)(input->getL());
		prodspare = new prodNode(spare->getR(), input->getR());
		changes.push_back(new fracNode(spare->getL(), prodspare));
		delete prodspare;
	}

	// attempt to evaluate (exact integers only)
	if ((input->getL()->type() == nodeTypes::num) 
		&& (input->getR()->type() == nodeTypes::num)
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
	if ((input->getR()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getR()))->get() == 1)
	{
		changes.push_back(input->getL()->copy());
	}

	//handle zero
	if ((input->getL()->type() == nodeTypes::num) 
		&& ((numNode*)(input->getL()))->get() == 0)
	{
		changes.push_back(new numNode(0));
	}

	// reduce to one
	if (input->getL()->eq(input->getR()))
	{
		changes.push_back(new numNode(1));
	}

	//handle same exp
	if (input->getL()->type() == nodeTypes::hat
		&& input->getR()->type() == nodeTypes::hat)
	{
		hat1spare = (hatNode*)(input->getL());
		hat2spare = (hatNode*)(input->getR());
	
		if (hat1spare->getR()->eq(hat2spare->getR()))
		{
			spare = new fracNode(hat1spare->getL(), hat2spare->getL());
			
			changes.push_back(new hatNode(spare, hat1spare->getR()));
			delete spare;
		}
	}

	//handle denominator expo
	if (input->getR()->type() == nodeTypes::hat)
	{
		hat1spare = (hatNode*)(input->getR());
		negspare = new negNode(hat1spare->getR());
		hat2spare = new hatNode(hat1spare->getL(),negspare);
		changes.push_back(new prodNode(input->getL(), hat2spare));
		delete negspare;
		delete hat2spare;
	}

	//numerator extraction 
	if (input->getL()->type() == nodeTypes::prod) 
	{
		prodspare = (prodNode*)(input->getL());
		spare = new fracNode(prodspare->getR(), input->getR());
		changes.push_back( new prodNode(prodspare->getL(), spare));
		delete spare;
	}

	return changes;
}
