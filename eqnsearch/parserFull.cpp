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
#include "parserFull.h"

using namespace std;

void parserFull::deleteList(vector<pair<int, eqnNode*> > list)
{
	int i;
	for (i = 0; i < (int)list.size(); i++)
	{
		if (list[i].second != 0) { delete list[i].second; }
	}
}

void parserFull::freeMap(map< pair<int, int>, vector<pair<int, eqnNode*> > > fails)
{
	map< pair<int, int>, vector<pair<int, eqnNode*> > >::iterator it;

	for (it=fails.begin(); it!=fails.end(); it++)
		{ deleteList((*it).second); }
}


eqnNode* parserFull::getExpr(string input) 
{
	int i;
	expParse d;
//	string parsethis = "(1+(32*4)-43688)*8*9*1209";
	
	d.setMap(&fails);

	d.loadString(0, input, 0);

	for (i = 0; i < (int)d.getTrees().size(); i++)
	{
		if (d.getTrees()[i].first == (int)input.length())
		{
			 return d.getTrees()[i].second->copy();
		}
	}
	return 0;
}

parserFull::~parserFull()
{
	freeMap(fails);
}
