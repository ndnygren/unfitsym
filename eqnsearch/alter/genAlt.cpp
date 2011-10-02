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
#include "templateMatcher.h"

using namespace std;

vector<eqnNode*> alterExpression::getCand(eqnNode* input)
{
	unsigned int i;
	numNode one(1);
	numNode negone(-1);
	vector<eqnNode*> changes;
	vector<eqnNode*> sumChanges;

	if (input->type() != nodeTypes::ident)	
	{
		subNode *subzero = new subNode(&one,&one);
		hatNode *hatspare = new hatNode(input, &negone);
		changes.push_back(new sumNode(input, subzero));
		changes.push_back(new prodNode(input, &one));
		changes.push_back(new prodNode(&one,input));
		changes.push_back(new hatNode(input, &one));
		changes.push_back(new fracNode(&one,hatspare));
		delete subzero;
		delete hatspare;
	}

	sumChanges = templateMatcher::getMatches(input);
	copyCand(sumChanges, changes);
	sumChanges.clear();

	if (input->type() == nodeTypes::sum)
		{ changes.push_back(sumSimplify((sumNode*)input)); }

	if (input->type() == nodeTypes::sub)
		{ sumChanges = subCand((subNode*)input); }
	else if (input->type() == nodeTypes::prod)
		{ sumChanges = prodCand((prodNode*)input); }
	else if (input->type() == nodeTypes::frac)
		{ sumChanges = fracCand((fracNode*)input); }
	else if (input->type() == nodeTypes::hat)
		{ sumChanges = hatCand((hatNode*)input); }
	else if (input->type() == nodeTypes::deriv)
		{ sumChanges = derivCand((derivNode*)input); }
	else if (input->type() == nodeTypes::integral)
		{ sumChanges = intCand((intNode*)input); }
	else if (input->type() == nodeTypes::integralb)
		{ sumChanges = intBCand((intBNode*)input); }
	else if (input->type() == nodeTypes::ident)
		{ sumChanges = idCand((idNode*)input); }
	else if (input->isMono())
	{
		sumChanges = getCand(((monoOpNode*)input)->getR());
		for (i = 0; i < sumChanges.size(); i++)
		{
			changes.push_back(((monoOpNode*)input)->new_node(sumChanges[i]));
			delete sumChanges[i];
		}
		sumChanges.clear();
	}
	else if (input->isBin())
	{
		sumChanges = getCand(((binOpNode*)input)->getR());
		for (i = 0; i < sumChanges.size(); i++)
		{
			changes.push_back(((binOpNode*)input)->new_node( ((binOpNode*)input)->getL(), sumChanges[i]));
			delete sumChanges[i];
		}
		sumChanges.clear();
		sumChanges = getCand(((binOpNode*)input)->getL());
		for (i = 0; i < sumChanges.size(); i++)
		{
			changes.push_back(((binOpNode*)input)->new_node(sumChanges[i], ((binOpNode*)input)->getR()));
			delete sumChanges[i];
		}
		sumChanges.clear();
	}

	copyCand(sumChanges, changes);
	sumChanges.clear();

	return changes;
}

void alterExpression::copyCand(const vector<eqnNode*>& from, vector<eqnNode*>& to)
{
	unsigned int i;
	for (i = 0; i < from.size(); i++)
	{
		to.push_back(from[i]);
	}
}

void alterExpression::freeCand(vector<eqnNode*>& list)
{
	unsigned int i;
	for (i = 0; i < list.size(); i++)
	{
		if (list[i] != 0)
		{
			delete list[i];
		}
	}
}
