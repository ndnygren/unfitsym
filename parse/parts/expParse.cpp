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
#include "expParse.h"
#include <vector>
#include <iostream>

using namespace std;

void expParse::loadString(int offset, const std::string& data, int cap)
{
	int j;
	natParse number;
	sumParse sums;
	subParse diff;
	std::vector<parsePart*> exprs;
	
	exprs.push_back(&number);
	exprs.push_back(&sums);
	exprs.push_back(&diff);

	deleteAll();
	
	if ((offset < (int)data.size() - cap) 
		&& ((*fails)[pair<int,int>(offset,cap)] != -1))
	{
		for (j = 0; j < (int)exprs.size(); j++)
		{
			exprs[j]->setMap(fails);
			exprs[j]->loadString(offset, data, cap);
			copySucc(exprs[j]->getTrees()); 
		}
	
		if (succ.size() == 0) 
		{
			(*fails)[pair<int,int>(offset,cap)] = -1; 
			cout << "no solutions found for " << offset << " " << cap << "\n";
		}
	}
/*	for (i = 0; i< succ.size(); i++)
	{
		std::cout << offset << "==>" << succ[i].first;
		if (succ[i].second != 0)
		{
			std::cout << "==>" << succ[i].second->str()
				<< "\n";
		}
		else { std::cout << "\n"; }
	}*/
}

expParse::expParse()
{
}
