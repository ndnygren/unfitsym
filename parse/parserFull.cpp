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
		// free all non-null pointers in the vector
		if (list[i].second != 0) { delete list[i].second; }
	}
}

void parserFull::freeMap(map< pair<int, int>, vector<pair<int, eqnNode*> > > fails)
{
	map< pair<int, int>, vector<pair<int, eqnNode*> > >::iterator it;
	
	// calls deleteList on every element stored in the map,
	//	freeing all non-null eqnNode* pointers
	for (it=fails.begin(); it!=fails.end(); it++)
		{ deleteList((*it).second); }
}


eqnNode* parserFull::getExpr(string input1) 
{
	int i;
	// expParse represents the main variable in the CFG, 
	//	any arithmetic expression.
	expParse d;
	string input = stripwhite(input1, &w_only);

	// the cache is pasted down when recursing, so the same sub-strings	
	// 	will not be parsed twice.
	d.setMap(&fails);

	// the lower(offset) and upper(cap) bounds are set to zero in the 
	//	beginning
	d.loadString(0, input, 0);

	for (i = 0; i < (int)d.getTrees().size(); i++)
	{
		// if too few brackets are used multiple interpretations 
		//	may exist. the first interpretation which utilizes all
		// 	supplied characters is assumed to be the correct one.
		if (d.getTrees()[i].first == (int)input.length())
		{
		// a copy is returned. The original is freed when the 
		//	function returns.
			 return d.getTrees()[i].second->copy();
		}
	}
	// returns null if no such interpretations exist
	return 0;
}

parserFull::~parserFull()
{
	freeMap(fails);
}
