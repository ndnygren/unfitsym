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
#include <iostream>
#include "parts/expParse.h"

using namespace std;

std::ostream& operator<<(std::ostream& lhs, const eqnNode& rhs)
{
	lhs << rhs;
	return lhs;
}

void deleteList(vector<pair<int, eqnNode*> > list)
{
	int i;
	for (i = 0; i < (int)list.size(); i++)
	{
		if (list[i].second != 0) { delete list[i].second; }
	}
}

void freeMap(map< pair<int, int>, vector<pair<int, eqnNode*> > > fails)
{
	map< pair<int, int>, vector<pair<int, eqnNode*> > >::iterator it;

	for (it=fails.begin(); it!=fails.end(); it++)
		{ deleteList((*it).second); }
}

int main()
{
	int i;
	expParse d;
	map< pair<int, int>, vector<pair<int, eqnNode*> > > fails;
	string parsethis = "(1+(x*32*4)-43688)*8*9*1209+\\frac{1}{1}";
	d.setMap(&fails);

	d.loadString(0, parsethis, 0);

	for (i = 0; i < (int)d.getTrees().size(); i++)
	{
		if (d.getTrees()[i].first <= (int)parsethis.length())
		{
			cout << i << ": " << d.getTrees()[i].first;
			if(d.getTrees()[i].second != 0)
				{ cout << ", " << d.getTrees()[i].second->str() << "\n"; }
			else { cout << "\n"; }
		}
	}

	freeMap(fails);
	return 0;
}
