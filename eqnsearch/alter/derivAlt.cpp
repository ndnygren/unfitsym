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
	int intspare;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	derivNode *spare, *otherspare;
	sumNode *sumspare;
	subNode *subspare;
	fracNode *fracspare, *frac1spare;
	prodNode *prodspare, *prod1spare, *prod2spare;
	numNode *num1spare, *num2spare;
	hatNode *hatspare, *hat2spare;
	numNode one(1);
	numNode two(2);
	cosineNode *cosspare;
	sineNode *sinspare;
	negNode *negspare;

	//check for constants
	if (input->getL()->isConst()) 
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

	// difference rule
	if (input->getL()->type() == nodeTypes::sub)
	{
		subspare = (subNode*)(input->getL());
		spare = new derivNode(subspare->getL(), input->getR());
		otherspare = new derivNode(subspare->getR(), input->getR());
		changes.push_back(new subNode(spare,otherspare));
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

	//product rule (half const)
	if (input->getL()->type() == nodeTypes::prod) 
	{
		prodspare = (prodNode*)(input->getL());
		if (prodspare->getL()->isConst())
		{
			spare = new derivNode(prodspare->getR(), input->getR());
			changes.push_back(new prodNode(prodspare->getL(),spare));
			delete spare;
		}
	}

	//quotient rule
	if (input->getL()->type() == nodeTypes::frac)
	{
		fracspare = (fracNode*)(input->getL());
		spare = new derivNode(fracspare->getL(), input->getR());
		otherspare = new derivNode(fracspare->getR(), input->getR());
		prod1spare = new prodNode(spare, fracspare->getR());
		prod2spare = new prodNode(otherspare, fracspare->getL());
		subspare = new subNode(prod1spare,prod2spare);
		hatspare = new hatNode(fracspare->getR(),&two);

		changes.push_back(new fracNode(subspare,hatspare));

		delete spare;
		delete otherspare;
		delete prod1spare;
		delete prod2spare;
		delete subspare;
		delete hatspare;
	}

	//quotient rule(numerator const)
	if (input->getL()->type() == nodeTypes::frac)
	{
		fracspare = (fracNode*)(input->getL());
		if (fracspare->getL()->isConst())
		{
			spare = new derivNode(fracspare->getR(), input->getR());
			prod1spare = new prodNode(spare, fracspare->getL());
			negspare = new negNode(prod1spare);
			hatspare = new hatNode(fracspare->getR(),&two);

			changes.push_back(new fracNode(negspare,hatspare));

			delete spare;
			delete prod1spare;
			delete negspare;
			delete hatspare;
		}
	}

	//quotient rule(denominiator const)
	if (input->getL()->type() == nodeTypes::frac)
	{
		fracspare = (fracNode*)(input->getL());
		if (fracspare->getR()->isConst())
		{
			spare = new derivNode(fracspare->getL(), input->getR());
			frac1spare = new fracNode(&one, fracspare->getR());

			changes.push_back(new prodNode(spare, frac1spare));

			delete spare;
			delete frac1spare;
		}
	}

	//power rule
	if (input->getL()->type() == nodeTypes::hat) 
	{
		hatspare = (hatNode*)(input->getL());
		if (hatspare->getR()->type() == nodeTypes::num)
		{
			intspare = ((numNode*)(hatspare->getR()))->get();
			num1spare = new numNode(intspare);
			if (intspare != 0)
				{ num2spare = new numNode(intspare-1); }
			else
				{ num2spare = new numNode(0); }
			hat2spare = new hatNode(hatspare->getL(),num2spare);
			prodspare = new prodNode(num1spare, hat2spare);
			spare = new derivNode(hatspare->getL(),input->getR());
				
			changes.push_back(new prodNode(prodspare,spare));
	
			delete num1spare;
			delete num2spare;
			delete hat2spare;
			delete prodspare;
			delete spare;
		}
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

	// cosine derivative
	if (input->getL()->type() == nodeTypes::cos)
	{
		cosspare = (cosineNode*)(input->getL());
		sinspare = new sineNode(cosspare->getR());
		spare = new derivNode(cosspare->getR(), input->getR());
		prodspare = new prodNode(sinspare, spare);
		changes.push_back(new negNode(prodspare));
		delete sinspare;
		delete prodspare;
		delete spare;
	}

	// sine derivative
	if (input->getL()->type() == nodeTypes::sin)
	{
		sinspare = (sineNode*)(input->getL());
		cosspare = new cosineNode(sinspare->getR());
		spare = new derivNode(sinspare->getR(), input->getR());
		changes.push_back(new prodNode(cosspare,spare));
		delete cosspare;
		delete spare;
	}

	return changes;
}
