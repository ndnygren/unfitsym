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

#include "../../parse/nodes/sumNode.h"
#include "../../parse/nodes/subNode.h"
#include "../../parse/nodes/prodNode.h"
#include "../../parse/nodes/fracNode.h"
#include "../../parse/nodes/negNode.h"
#include "../../parse/nodes/cosineNode.h"
#include "../../parse/nodes/sineNode.h"
#include "../../parse/nodes/lnNode.h"
#include "../../parse/nodes/varNode.h"
#include "../../parse/nodes/hatNode.h"
#include "../../parse/nodes/idxNode.h"

using namespace std;

eqnNode* alterExpression::substitute(prodNode* input, string var)
{
	eqnNode *outexpr, *temp1, *temp2, *temp3;
	sumNode *sumspare;
	fracNode *fracspare;
	hatNode *hatspare;
	negNode *negspare;
	sineNode *sinspare;
	cosineNode *cosspare;
	numNode one(1);
	numNode two(2);

	//simplest case \int f(u)du/dx dx
	temp1 = derivative(input->getR(),var);
	temp3 = temp1->collapse();
	temp2 = scalarCompare(input->getL(), temp3);
	delete temp1;
	delete temp3;

	if (temp2 != 0)
	{
		hatspare = new hatNode(input->getR(), &two);
		fracspare = new fracNode(temp2, &two);
		outexpr = new prodNode(fracspare, hatspare);
		delete hatspare;
		delete fracspare;
		delete temp2;
		return outexpr;
	}

	//polynomial types
	if (input->getR()->type() == nodeTypes::hat
		&& ((hatNode*)input->getR())->getR()->isConst())
	{
		temp1 = derivative(((hatNode*)input->getR())->getL(), var);
		temp2 = scalarCompare(input->getL(),temp1);
		delete temp1;

		if (temp2 != 0)
		{
			sumspare = new sumNode(((hatNode*)input->getR())->getR(), &one);
			hatspare = new hatNode(((hatNode*)input->getR())->getL(), sumspare);
			fracspare = new fracNode(temp2, sumspare);
			outexpr = new prodNode(fracspare,hatspare);
			delete fracspare;
			delete hatspare;
			delete sumspare;
			delete temp2;
			return outexpr;
		}
	}

	//cosine
	if (input->getR()->type() == nodeTypes::cos)
	{
		cosspare = (cosineNode*)(input->getR());
		temp1 = derivative(cosspare->getR(), var);
		temp2 = scalarCompare(input->getL(), temp1);
		delete temp1;

		if (temp2 != 0)
		{
			sinspare = new sineNode(cosspare->getR());
			outexpr = new prodNode(temp2, sinspare);
			delete sinspare;
			delete temp2;
			return outexpr;
		}
	}

	//sine
	if (input->getR()->type() == nodeTypes::sin)
	{
		sinspare = (sineNode*)(input->getR());
		temp1 = derivative(sinspare->getR(), var);
		temp2 = scalarCompare(input->getL(), temp1);
		delete temp1;

		if (temp2 != 0)
		{
			cosspare = new cosineNode(sinspare->getR());
			negspare = new negNode(cosspare);
			outexpr = new prodNode(temp2, negspare);
			delete cosspare;
			delete negspare;
			delete temp2;
			return outexpr;
		}
	}

	return 0;
}

eqnNode* alterExpression::attemptStrip(intNode* input)
{
	eqnNode *outexpr, *left, *right;
	sumNode *sumspare;
	intNode *intleftspare, *intrightspare; 
	prodNode *prodspare;
	hatNode *hatspare, *hat1spare;
	numNode one(1);
	numNode negone(-1);
	numNode two(2);
	numNode zero(0);
	varNode *varspare;

	//recurse into sums
	if (input->getL()->type() == nodeTypes::sum)
	{
		sumspare = (sumNode*)(input->getL());
		intleftspare = new intNode(sumspare->getL(), input->getR());
		intrightspare = new intNode(sumspare->getR(), input->getR());
		left = attemptStrip(intleftspare);
		right = attemptStrip(intrightspare);
		delete intleftspare;
		delete intrightspare;
		
		if (left != 0 && right != 0)
		{
			outexpr = new sumNode(left,right);
			delete left;
			delete right;
			return outexpr;
		}
		else if (left != 0) { delete left; }
		else if (right != 0) { delete right; }
	}

	//check for constants
	if (input->getL()->isConst()) 
	{
		outexpr = new prodNode(input->getL(),input->getR());
		return outexpr;
	}
	else if (input->getR()->type() == nodeTypes::var
		&& input->getL()->isConst(((varNode*)input->getR())->get())) 
	{
		return new prodNode(input->getL(),input->getR());
	}

	//check equality
	if (input->getL()->eq(input->getR()))
	{
		hatspare = new hatNode(input->getL(),&two);
		outexpr = new fracNode(hatspare,&two);
		delete hatspare;
		return outexpr;
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
				outexpr = new fracNode(hat1spare,sumspare);
				delete hat1spare;
				delete sumspare;
				return outexpr;
			}
			else
			{
				outexpr = new lnNode(hatspare->getL());
				return outexpr;
			}
		}
	}



	//for products, attempt substitution of variables
	if (input->getL()->type() == nodeTypes::prod
		&& input->getR()->type() == nodeTypes::var)
	{
		outexpr = substitute((prodNode*)input->getL(), ((varNode*)input->getR())->get());
		if (outexpr != 0) { return outexpr; }
	}
	else if (input->getR()->type() == nodeTypes::var)
	{
		prodspare = new prodNode(&one, input->getL());
		outexpr = substitute(prodspare, ((varNode*)input->getR())->get());
		delete prodspare;
		if (outexpr != 0) { return outexpr; }
	}

	return 0;
}
