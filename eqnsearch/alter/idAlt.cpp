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

vector<eqnNode*> alterExpression::idCand(idNode* input)
{
	unsigned int i;
	vector<eqnNode*> changes;
	vector<eqnNode*> subchanges;
	idNode *spare;
	sumNode *sum1spare, *sum2spare;
	subNode *subspare;
	fracNode *fracspare;
	prodNode *prodspare;

	//commute
	changes.push_back(new idNode(input->getR(), input->getL()));


	// cancellation (additive)
	if (input->getL()->type() == nodeTypes::sum
		&& input->getR()->type() == nodeTypes::sum)
	{
		sum1spare = (sumNode*)input->getL();
		sum2spare = (sumNode*)input->getR();
		if (sum1spare->getR()->eq(sum2spare->getR()))
		{
			changes.push_back(new idNode(sum1spare->getL(),sum2spare->getL()));
		}
	}

	//moving term (additive)
	if (input->getL()->type() == nodeTypes::sum)
	{
		sum1spare = (sumNode*)input->getL();
		subspare = new subNode(input->getR(), sum1spare->getR());
		changes.push_back(new idNode(sum1spare->getL(),subspare));
		delete subspare;
	}

	//moving factor (numerator)
	if (input->getL()->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)input->getL();
		if (prodspare->getL()->isConst()
			&& prodspare->getL()->value()!= 0)
		{
			fracspare = new fracNode(input->getR(), prodspare->getL());
			changes.push_back(new idNode(prodspare->getR(),fracspare));
			delete fracspare;
		}
	}

	//moving factor (denominator)
	if (input->getL()->type() == nodeTypes::frac)
	{
		fracspare = (fracNode*)input->getL();
		prodspare = new prodNode(input->getR(), fracspare->getR());
		changes.push_back(new idNode(fracspare->getL(),prodspare));
		delete prodspare;
	}

	//recursing
	copyCand(getCand(input->getL()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new idNode(subchanges[i], input->getR());
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	copyCand(getCand(input->getR()), subchanges);
	for (i = 0; i< subchanges.size(); i++)
	{
		spare = new idNode(input->getL(), subchanges[i]);
		changes.push_back(spare);
	}
	freeCand(subchanges);
	subchanges.clear();

	return changes;
}
