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


vector<eqnNode*> alterExpression::intBCand(intBNode* input)
{
	unsigned int i;
	eqnNode *stripped, *stripped2, *deriv, *temp, *temp2;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	intBNode *spare, *otherspare;
	sumNode *sumspare;
	subNode *subspare;
	fracNode *fracspare, *frac1spare;
	prodNode *prodspare, *prod1spare;
	numNode one(1);
	numNode negone(-1);
	numNode two(2);
	numNode zero(0);
	varNode c("C");
	varNode r("replace");
	idxNode rep(&c,&r);
	std::string var1;
	


	// sums
	if (input->getL()->type() == nodeTypes::sum) 
	{
		sumspare = (sumNode*)(input->getL());
		spare = new intBNode(sumspare->getL(), input->getR(), input->getUpper(), input->getLower());
		otherspare = new intBNode(sumspare->getR(), input->getR(), input->getUpper(), input->getLower());
		changes.push_back(new sumNode(spare,otherspare));
		delete spare;
		delete otherspare;
	}

	// difference rule
	if (input->getL()->type() == nodeTypes::sub)
	{
		subspare = (subNode*)(input->getL());
		spare = new intBNode(subspare->getL(), input->getR(), input->getUpper(), input->getLower());
		otherspare = new intBNode(subspare->getR(), input->getR(), input->getUpper(), input->getLower());
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
			spare = new intBNode(prodspare->getR(), input->getR(), input->getUpper(), input->getLower());
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
			spare = new intBNode(frac1spare, input->getR(), input->getUpper(), input->getLower());

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
			spare = new intBNode(fracspare->getL(), input->getR(), input->getUpper(), input->getLower());
			frac1spare = new fracNode(&one, fracspare->getR());

			changes.push_back(new prodNode(spare, frac1spare));

			delete spare;
			delete frac1spare;
		}
	}


	//attempt to solve
	if (input->getR()->type() == nodeTypes::var)
	{
		var1 = ((varNode*)input->getR())->get();
		stripped = attemptStrip(input);
		if (stripped != 0)
		{
			stripped2 = stripped->copy();
			
			if (stripped->isVar(var1))
			{
				delete stripped;
				stripped = input->getUpper();
			}
			else { stripped->replace(var1, input->getUpper()); }
			if (stripped2->isVar(var1))
			{
				delete stripped2;
				stripped2 = input->getLower()->copy();
			}
			else { stripped2->replace(var1, input->getLower()); }
			
			
			changes.push_back(new subNode(stripped, stripped2));
			delete stripped;
			delete stripped2;
		}
	}
	
	//by parts
	if (input->getL()->type() == nodeTypes::prod && input->getR()->type() == nodeTypes::var)
	{
		prodspare = (prodNode*)input->getL();
		spare = new intBNode(prodspare->getL(), input->getR(), input->getUpper(), input->getLower());
		stripped = attemptStrip(spare);
		delete spare;
		if (stripped != 0)
		{
			deriv = derivative(prodspare->getR(), ((varNode*)input->getR())->get());
			prodspare = new prodNode(stripped, prodspare->getR());
			temp = prodspare->collapse();
			prod1spare = new prodNode(stripped, deriv);
			temp2 = prod1spare->collapse();
			spare = new intBNode(temp2, input->getR(), input->getUpper(), input->getLower());

			stripped2 = temp->copy();

			temp->replace(var1, input->getUpper());
			stripped2->replace(var1, input->getLower());
			subspare = new subNode(temp, stripped2);

			changes.push_back(new subNode(subspare, spare));
			delete spare;
			delete prodspare;
			delete prod1spare;
			delete deriv;
			delete stripped;
			delete stripped2;
			delete subspare;
			delete temp;
			delete temp2;
		}
	}	

	//recursing
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new intBNode(subchanges[i], input->getR(),input->getUpper(), input->getLower());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();


	return changes;
}
