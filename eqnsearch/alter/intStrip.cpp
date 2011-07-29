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

#include "intStrip.h"

using namespace std;

eqnNode* attemptStrip(intNode* input)
{
	eqnNode* outexpr;
	sumNode *sumspare;
	fracNode *fracspare;
	prodNode *prodspare;
	hatNode *hatspare, *hat1spare;
	numNode one(1);
	numNode negone(-1);
	numNode two(2);
	numNode zero(0);
	varNode *varspare;
	sineNode *sinspare;
	cosineNode *cosspare;

	//check for constants
	if (input->getL()->isConst()) 
	{
		outexpr = new prodNode(input->getL(),input->getR());
		return outexpr;
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

	//simple cosine
	if (input->getL()->type() == nodeTypes::cos
		&& input->getR()->type() == nodeTypes::var)
	{
		varspare = (varNode*)(input->getR());
		cosspare = (cosineNode*)(input->getL());
		if (cosspare->getR()->isVar(varspare->get()))
		{
			outexpr = new sineNode(cosspare->getR());
			return outexpr;
		}
		//slightly less simple \int \cos(c*x) d{x}
		else if (cosspare->getR()->type() == nodeTypes::prod)
		{
			prodspare = (prodNode*)(cosspare->getR());
			if (prodspare->getR()->isVar(varspare->get())
				&& prodspare->getL()->isConst(varspare->get()))
			{
				sinspare = new sineNode(prodspare);
				fracspare = new fracNode(&one,prodspare->getL());
				outexpr = new prodNode(fracspare, sinspare);
				delete fracspare;
				delete sinspare;
				return outexpr;
			}
		}
	}

	//simple sine
	if (input->getL()->type() == nodeTypes::sin
		&& input->getR()->type() == nodeTypes::var)
	{
		varspare = (varNode*)(input->getR());
		sinspare = (sineNode*)(input->getL());
		if (sinspare->getR()->isVar(varspare->get()))
		{
			cosspare = new cosineNode(sinspare->getR());
			outexpr = new negNode(cosspare);
			delete cosspare;
			return outexpr;
		}
		//slightly less simple \int \sin(c*x) d{x}
		else if (sinspare->getR()->type() == nodeTypes::prod)
		{
			prodspare = (prodNode*)(sinspare->getR());
			if (prodspare->getR()->isVar(varspare->get())
				&& prodspare->getL()->isConst(varspare->get()))
			{
				cosspare = new cosineNode(prodspare);
				fracspare = new fracNode(&negone,prodspare->getL());
				outexpr = new prodNode(fracspare, cosspare);
				delete fracspare;
				delete cosspare;
				return outexpr;
			}
		}
	}


	return 0;
}
