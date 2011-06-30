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

int main()
{
	int i;
	expParse d;
	map< pair<int,int>, int> fails;

	d.setMap(&fails);

	d.loadString(0,"189+25-3+7", 0);

	for (i = 0; i < (int)d.getTrees().size(); i++)
	{
		if (d.getTrees()[i].first == 8)
		{
			cout << i << ": " << d.getTrees()[i].first;
			if(d.getTrees()[i].second != 0)
				{ cout << ", " << d.getTrees()[i].second->str() << "\n"; }
			else
				{ cout << "\n"; }
		}
	}

	return 0;
}
