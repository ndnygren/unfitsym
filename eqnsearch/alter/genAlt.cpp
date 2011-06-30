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

#include "genAlt.h"
using namespace std;

vector<eqnNode*> getCand(eqnNode* input)
{
	nodeTypes types;
	vector<eqnNode*> changes;
	vector<eqnNode*> sumChanges;

	if (input->type() == types.sum)
	{
		sumChanges = sumCand((sumNode*)input);
	}
	copyCand(sumChanges, changes);
	sumChanges.clear();

	if (input->type() == types.sub)
	{
		sumChanges = subCand((subNode*)input);
	}
	copyCand(sumChanges, changes);
	sumChanges.clear();

	if (input->type() == types.prod)
	{
		sumChanges = prodCand((prodNode*)input);
	}
	copyCand(sumChanges, changes);
	sumChanges.clear();

	return changes;
}

void copyCand(const vector<eqnNode*>& from, vector<eqnNode*>& to)
{
	unsigned int i;
	for (i = 0; i < from.size(); i++)
	{
		to.push_back(from[i]);
	}
}

void freeCand(vector<eqnNode*>& list)
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
