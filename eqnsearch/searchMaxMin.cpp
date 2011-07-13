
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
#include "eqnMetric.h"
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

class eqnComp
{
	protected:
	eqnMetric *rate;

	public:
	bool operator() (const eqnNode* lhs, const eqnNode* rhs)
	{
		return rate->score(lhs) > rate->score(rhs);
	}

	eqnComp() { }
	
	eqnComp(eqnMetric* input)
		{ rate = input; }
};

class searchMaxMin
{
	protected:
	eqnComp comp;
	eqnMetric *rate;
	
	void freeMap(std::map<std::string, eqnNode*> &inmap)
	{
		std::map<std::string, eqnNode*>::iterator it;

		for (it=inmap.begin(); it!=inmap.end(); it++)
			{ delete (*it).second; }
	}

	public:
	eqnNode* start;
	std::vector<std::pair<std::string, std::string> > adjPairs;
	std::map<std::string, eqnNode*> exprMap;
	std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp> stack;

	searchMaxMin(eqnNode* input, eqnMetric* inrate)
	{
		rate = inrate; 
		comp = eqnComp(rate);
		stack = std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp>(comp);
		start = input->copy();
		stack.push(input->copy());
	
		next();
	}

	void next(int limit = 100)
	{
		unsigned int i;
		int count = 0;
		exprLinked* current;

		while (stack.size() > 0 && count < limit)
		{
			current = new exprLinked(stack.top());
			delete stack.top();
			stack.pop();
//			cout << current[0].str() << "\n";

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
					count++;
				}
			}
			delete current;
		}
	}

	std::vector<eqnNode*> best(unsigned int limit = 10)
	{
		unsigned int i;
		std::vector<eqnNode*> list;
		eqnNode *toinsert, *spare;
		std::map<std::string, eqnNode*>::iterator it;

		for (it=exprMap.begin(); it!=exprMap.end(); it++)
		{
			toinsert = (*it).second;
			for (i = 0; i < limit; i++)
			{
				if (i >= list.size())
				{
					list.push_back(toinsert);
					i = limit;
				}
				else if (rate->score(toinsert) < rate->score(list[i]))
				{
					spare = list[i];
					list[i] = toinsert;
					toinsert = spare;
				}
			}
		}

		return list;
		
	}

	~searchMaxMin()
	{
		freeMap(exprMap);

		//this is brutal, needs to be replaced with a iterator
		while (!stack.empty())
		{
			delete stack.top();
			stack.pop();
		}
		delete start;
	}
};
