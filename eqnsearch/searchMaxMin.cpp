
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

#include "../parse/nodes/eqnNode.h"
#include "exprLinked.h"
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

class eqnComp
{
	public:
	bool operator() (const eqnNode* lhs, const eqnNode* rhs)
	{
		return lhs->str().length() > rhs->str().length();
	}
};

class searchMaxMin
{
	protected:
	eqnNode* start;
	
	public:
	searchMaxMin(eqnNode* input)
	{
		unsigned int i;
		exprLinked* current = new exprLinked(input);
		std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp> stack;
		std::vector<eqnNode*> changes;
		std::vector<std::pair<std::string, std::string> > adjPairs;
		std::map<std::string, eqnNode*> exprMap;
		start = input;
		stack.push(input->copy());

		while (stack.size() > 0)
		{
			delete current;
			current = new exprLinked(stack.top());
			delete stack.top();
			stack.pop();
			cout << current[0].str() << "\n";

			current[0].load();

			for(i = 0; i < current[0].changes.size(); i++)
			{
				if (exprMap.count(current[0].changes[i]->str()) > 0)
				{
					adjPairs.push_back( std::pair<std::string,std::string> (current[0].str(), current[0].changes[i]->str()));
				}
				else
				{
					exprMap[current[0].changes[i]->str()] = current[0].changes[i]->copy();
					adjPairs.push_back( std::pair<std::string,std::string> (current[0].str(), current[0].changes[i]->str()));
					stack.push(current[0].changes[i]->copy());
				}
			}
		}
	}
};
