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

#include "sumParse.h"
#include <string>
#include <iostream>

void sumParse::loadString(int offset, const std::string& data, int cap)
{
	int i,j,k;
	expParse lefte;
	expParse righte;
	token plus("+");


	lefte.loadString(offset, data, cap + 1);
	for (i = 0; i < (int)lefte.getTrees().size(); i++)
	{
		plus.loadString(lefte.getTrees()[i].first, data, cap);
		for (j = 0; j < (int)plus.getTrees().size(); j++)
		{
			righte.loadString(plus.getTrees()[j].first, data, cap);
			for (k = 0; k < (int)righte.getTrees().size(); k++)
			{
				succ.push_back(std::pair<int,eqnNode*>(
					righte.getTrees()[k].first,
					new sumNode(
						lefte.getTrees()[i].second,
						righte.getTrees()[k].second
					)));
			}
		}
	}

}
