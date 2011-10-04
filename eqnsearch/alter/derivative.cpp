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
#include "../derivMetric.h"
#include "../searchMaxMin.h"

#include <cassert>

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

using namespace std;

eqnNode* alterExpression::derivative(eqnNode* input, const std::string& var)
{
	bool DERIV_NOT_FOUND = false;
	eqnNode *outexpr, *left, *right;
	sumNode *sumspare; 
	subNode *subspare; 
	prodNode *prodspare, *prod1spare, *prod2spare;
	fracNode *fracspare;
	sineNode *sinspare;
	cosineNode *cosspare;
	hatNode *hatspare, *hat1spare;
	lnNode *lnspare;
	numNode negone(-1), one(1), two(2);

	if (input->type() == nodeTypes::sum)
	{
		sumspare = (sumNode*)input;
		
		left = derivative(sumspare->getL(), var);
		right = derivative(sumspare->getR(), var);
		outexpr = new sumNode(left, right);
		delete left;
		delete right;
		return outexpr;
	}
	else if (input->type() == nodeTypes::sub)
	{
		subspare = (subNode*)input;
		
		left = derivative(subspare->getL(), var);
		right = derivative(subspare->getR(), var);
		outexpr = new subNode(left, right);
		delete left;
		delete right;
		return outexpr;
	}	
	else if (input->type() == nodeTypes::num)
	{
		return new numNode(0);
	}
	else if (input->type() == nodeTypes::var)
	{
		if (((varNode*)input)->get() == var)
			{ return new numNode(1); }
		else { return new numNode(0); }
	}
	else if (input->type() == nodeTypes::prod)
	{
		prodspare = (prodNode*)input;
		
		left = derivative(prodspare->getL(), var);
		right = derivative(prodspare->getR(), var);
		prod1spare = new prodNode(prodspare->getL(), right);
		prod2spare = new prodNode(left, prodspare->getR());

		outexpr = new sumNode(prod1spare, prod2spare);
		delete left;
		delete right;
		delete prod1spare;
		delete prod2spare;
		return outexpr;
	}
	else if (input->type() == nodeTypes::frac)
	{
		fracspare = (fracNode*)input;
		
		left = derivative(fracspare->getL(), var);
		right = derivative(fracspare->getR(), var);
		prod1spare = new prodNode(fracspare->getL(), right);
		prod2spare = new prodNode(left, fracspare->getR());

		subspare = new subNode(prod1spare, prod2spare);
		hatspare = new hatNode(fracspare->getR(),&two);
		outexpr = new fracNode(subspare, hatspare);

		delete left;
		delete right;
		delete subspare;
		delete hatspare;
		delete prod1spare;
		delete prod2spare;
		return outexpr;
	}
	else if (input->type() == nodeTypes::cos)
	{
		cosspare = (cosineNode*)input;
		left = derivative(cosspare->getR(), var);
		sinspare = new sineNode(cosspare->getR());
		prodspare = new prodNode(&negone, left);
		outexpr = new prodNode(prodspare,sinspare);

		delete left;
		delete sinspare;
		delete prodspare;
		return outexpr;
	}
	else if (input->type() == nodeTypes::sin)
	{
		sinspare = (sineNode*)input;
		left = derivative(sinspare->getR(), var);
		cosspare = new cosineNode(sinspare->getR());
		outexpr = new prodNode(left,cosspare);
		delete left;
		delete cosspare;
		return outexpr;
	}
	else if (input->type() == nodeTypes::hat && ((hatNode*)input)->getR()->isConst(var))
	{
		hatspare = (hatNode*)input;
		subspare = new subNode(hatspare->getR(), &one);
		left = derivative(hatspare->getL(), var);
		hat1spare = new hatNode(hatspare->getL(), subspare);
		prodspare = new prodNode(hatspare->getR(), left);
		outexpr = new prodNode(prodspare, hat1spare);
	
		delete subspare;
		delete prodspare;
		delete left;
		delete hat1spare;
		return outexpr;
	}
	else if (input->type() == nodeTypes::hat && ((hatNode*)input)->getL()->isConst(var))
	{
		hatspare = (hatNode*)input;
		lnspare = new lnNode(hatspare->getL());
		right = derivative(hatspare->getR(), var);
		prodspare = new prodNode(right, lnspare);
		outexpr = new prodNode(prodspare, input);

		delete lnspare;
		delete right;
		delete prodspare;
		return outexpr;
	}

	/* not even close to correct... needs to be replaced*/
	else if (input->type() == nodeTypes::integral
		|| input->type() == nodeTypes::integralb)
	{
		return ((intNode*)input)->getL()->copy();
	}
	else if (input->type() == nodeTypes::ln)
	{
		fracspare = new fracNode(&one, ((lnNode*)input)->getR());
		right = derivative(((lnNode*)input)->getR(),var);
		outexpr = new prodNode(fracspare,right);

		delete fracspare;
		delete right;
		return outexpr;
	}
	else if (input->type() == nodeTypes::neg)
	{
		right = derivative(((negNode*)input)->getR(),var);
		outexpr = new negNode(right);
		
		delete right;
		return outexpr;
	}
	else if (input->type() == nodeTypes::idx)
	{
		return new numNode(0);
	}

	assert(DERIV_NOT_FOUND);

	return 0;
}
