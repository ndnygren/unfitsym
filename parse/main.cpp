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
#include "parts/tokParse.h"
#include "parts/altParse.h"
#include "parts/seqParse.h"
#include "parts/natParse.h"

using namespace std;

int main()
{
	int i;
	natParse d;	

	d.loadString(0,"1024.9342");

	for (i = 0; i < d.getTrees().size(); i++)
	{
		cout << i << ": " << d.getTrees()[i].first;
		if(d.getTrees()[i].second != 0)
			{ cout << ", " << d.getTrees()[i].second->str() << "\n"; }
		else
			{ cout << "\n"; }
	}

	return 0;
}
