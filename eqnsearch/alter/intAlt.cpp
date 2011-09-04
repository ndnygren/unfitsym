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

int alterExpression::maxIndex(eqnNode* input)
{
	varNode c("C");

	if (input->type() == nodeTypes::idx
		&& ((idxNode*)input)->getL()->eq(&c)
		&& ((idxNode*)input)->getR()->isConst())
		{ return (int)(((idxNode*)input)->getR()->value()); }
	else if (input->isBin())
	{
		return binOpNode::max(maxIndex(((binOpNode*)input)->getL()) ,maxIndex(((binOpNode*)input)->getR()));
	}
	else if (input->isMono())
	{
		return maxIndex(((monoOpNode*)input)->getR());
	}

	return 0;
}

void alterExpression::setIndex(eqnNode* input, int newindex)
{
	varNode c("C");
	varNode r("replace");
	idxNode rep(&c,&r);

	if (input->eq(&rep))
	{
		((idxNode*)input)->setIdx(newindex);
	}
	else if (input->isBin())
	{
		setIndex(((binOpNode*)input)->getL(), newindex); 
		setIndex(((binOpNode*)input)->getR(), newindex);
	}
	else if (input->isMono())
	{
		setIndex(((monoOpNode*)input)->getR(), newindex);
	}
}

vector<eqnNode*> alterExpression::intCand(intNode* input)
{
	unsigned int i;
	eqnNode *stripped, *deriv, *temp, *temp2;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	intNode *spare, *otherspare;
	sumNode *sumspare;
	subNode *subspare;
	negNode *negspare;
	fracNode *fracspare, *frac1spare;
	prodNode *prodspare, *prod1spare;
	numNode one(1);
	numNode negone(-1);
	numNode two(2);
	numNode zero(0);
	varNode c("C");
	varNode r("replace");
	idxNode rep(&c,&r);
	


	// neg
	if (input->getL()->type() == nodeTypes::neg) 
	{
		negspare = (negNode*)(input->getL());
		spare = new intNode(negspare->getR(), input->getR());
		changes.push_back(new negNode(spare));
		delete spare;
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


	//attempt to solve
	stripped = attemptStrip(input);
	if (stripped != 0)
	{
		changes.push_back(new sumNode(stripped, &rep));
		delete stripped;
	}

	//by parts
	if (input->getL()->type() == nodeTypes::prod && input->getR()->type() == nodeTypes::var)
	{
		prodspare = (prodNode*)input->getL();
		spare = new intNode(prodspare->getL(), input->getR());
		stripped = attemptStrip(spare);
		delete spare;
		if (stripped != 0)
		{
			deriv = derivative(prodspare->getR(), ((varNode*)input->getR())->get());
			prodspare = new prodNode(stripped, prodspare->getR());
			temp = prodspare->collapse();
			prod1spare = new prodNode(stripped, deriv);
			temp2 = prod1spare->collapse();
			spare = new intNode(temp2, input->getR());
			changes.push_back(new subNode(temp, spare));
			delete spare;
			delete prodspare;
			delete prod1spare;
			delete temp;
			delete temp2;
			delete deriv;
			delete stripped;
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
