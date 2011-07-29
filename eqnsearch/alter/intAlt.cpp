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

#include "intAlt.h"

using namespace std;

vector<eqnNode*> intCand(intNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	intNode *spare, *otherspare;
	sumNode *sumspare;
	subNode *subspare;
	fracNode *fracspare, *frac1spare;
	prodNode *prodspare;
	hatNode *hatspare, *hat1spare;
	numNode one(1);
	numNode negone(-1);
	numNode two(2);
	numNode zero(0);
	varNode *varspare;

	//check for constants
	if (input->getL()->isConst()) 
	{
		changes.push_back(new prodNode(input->getL(),input->getR()));
	}

	//check equality
	if (input->getL()->eq(input->getR()))
	{
		hatspare = new hatNode(input->getL(),&two);
		changes.push_back(new fracNode(hatspare,&two));
		delete hatspare;
	}

	// sums
	if (input->getL()->type() == nodeTypes::sum) 
	{
		sumspare = (sumNode*)(input->getL());
		spare = new intNode(sumspare->getL(), input->getR());
		otherspare = new intNode(sumspare->getR(), input->getR());
		changes.push_back(new sumNode(spare,otherspare));
		delete spare;
		delete otherspare;
	}

	// difference rule
	if (input->getL()->type() == nodeTypes::sub)
	{
		subspare = (subNode*)(input->getL());
		spare = new intNode(subspare->getL(), input->getR());
		otherspare = new intNode(subspare->getR(), input->getR());
		changes.push_back(new subNode(spare,otherspare));
		delete spare;
		delete otherspare;
	}

	//handle half-constant products
	if (input->getL()->type() == nodeTypes::prod) 
	{
		prodspare = (prodNode*)(input->getL());
		if (prodspare->getL()->isConst())
		{
			spare = new intNode(prodspare->getR(), input->getR());
			changes.push_back(new prodNode(prodspare->getL(),spare));
			delete spare;
		}
	}

	// handle constant numerator quotients 
	if (input->getL()->type() == nodeTypes::frac)
	{
		fracspare = (fracNode*)(input->getL());
		if (fracspare->getL()->isConst())
		{
			frac1spare = new fracNode(&one, fracspare->getR());
			spare = new intNode(frac1spare, input->getR());

			changes.push_back( new prodNode(spare, fracspare->getL()));

			delete frac1spare;
			delete spare;
		}
	}

	// handle constant denominator quotients
	if (input->getL()->type() == nodeTypes::frac)
	{
		fracspare = (fracNode*)(input->getL());
		if (fracspare->getR()->isConst())
		{
			spare = new intNode(fracspare->getL(), input->getR());
			frac1spare = new fracNode(&one, fracspare->getR());

			changes.push_back(new prodNode(spare, frac1spare));

			delete spare;
			delete frac1spare;
		}
	}

	//polynomial types
	if (input->getL()->type() == nodeTypes::hat
		&& input->getR()->type() == nodeTypes::var)
	{
		hatspare = (hatNode*)(input->getL());
		varspare = (varNode*)(input->getR());
		if (hatspare->getR()->isConst(varspare->get())
			&& hatspare->getL()->eq(varspare))
		{
			if (!(hatspare->getR()->eqVal(&negone)))
			{
				sumspare = new sumNode(hatspare->getR(), &one);
				hat1spare = new hatNode(hatspare->getL(), sumspare);
				changes.push_back(new fracNode(hat1spare,sumspare));
				delete hat1spare;
				delete sumspare;
			}
			else
				{ changes.push_back(new lnNode(hatspare->getL())); }
		}
	}

	//recursing
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new intNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();


	return changes;
}
