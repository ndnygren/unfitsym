
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

#include "searchMaxMin.h"

using namespace std;

	
void searchMaxMin::freeMap(std::map<std::string, eqnNode*> &inmap)
{
	std::map<std::string, eqnNode*>::iterator it;

	for (it=inmap.begin(); it!=inmap.end(); it++)
		{ delete (*it).second; }
}

void searchMaxMin::allPush(eqnNode* input)
{
	unsigned int i;

	for (i = 0; i < stacks.size(); i++)
	{
		stacks[i].push(input->copy());
	}
}

searchMaxMin::searchMaxMin(eqnNode* input, eqnMetric* inrate)
{
	rate = inrate; 
	comp = eqnComp(rate);
	// the proiority_queue is initialized with the supplied metric here
	stacks.push_back( std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp>(comp));
	// a first value is entered into the search
	start = input->copy();
	allPush(input);

	next();
}

void searchMaxMin::addNewDirection(eqnMetric* inrate)
{
	stacks.push_back( std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp>(eqnComp(inrate)));
}

void searchMaxMin::addToMap(std::string from, eqnNode *newnode)
{
	// if it already exists, we only add the new path
	if (exprMap.count(newnode->str()) > 0)
	{
		adjPairs.push_back( std::pair<std::string,std::string> (from, newnode->str()));
	}
	else // otherwise it is new discovery
	{
		exprMap[newnode->str()] = newnode->copy();
		adjPairs.push_back( std::pair<std::string,std::string> (from, newnode->str()));
		//it is added to the stack to be evaluated itself
		allPush(newnode);
	}
}

void searchMaxMin::next(int limit)
{
	unsigned int i;
	int count = 0;
	unsigned int cs = 0;


	// exprLinked interacts with the expression manipulators 
	//	(stored in eqnsearch/alter/)
	// 	and returns a list of expressions to add to the adjacent
	//	pairs list
	exprLinked* current;

	// the stack should never empty itself, but this is left in
	// 	in case the rules about identity (+0, *1) are removed.
	while (stacks[0].size() > 0 && count < limit)
	{
		//chooses a particular direction and selects an expresion
		if (cs >= stacks.size()) { cs = 0; }
		current = new exprLinked(stacks[cs].top());
		delete stacks[cs].top();
		stacks[cs].pop();
		cs++;	

		// load() generates fresh candidates from the current 
		// expression
		current[0].load();

		for(i = 0; i < current[0].changes.size(); i++)
		{
			addToMap(current[0].str(), current[0].changes[i]);
			count++;
		}
		delete current;
	}
}

std::vector<eqnNode*> searchMaxMin::best(unsigned int limit)
{
	unsigned int i;
	std::vector<eqnNode*> list;
	eqnNode *toinsert, *spare;
	std::map<std::string, eqnNode*>::iterator it;

	for (it=exprMap.begin(); it!=exprMap.end(); it++)
	{
		//iterate over the map in a single pass
		toinsert = (*it).second;
		for (i = 0; i < limit; i++)
		{
			if (i >= list.size())//begin by filling the list
			{
				list.push_back(toinsert);
				i = limit;
			}
			else if (rate->score(toinsert) < rate->score(list[i]))
			//if the current candidate is better than
			//	what is already in the list, swap
			{
				spare = list[i];
				list[i] = toinsert;
				toinsert = spare;
			}
		}
	}

	return list;
	
}

searchMaxMin::~searchMaxMin()
{
	unsigned int i;
	freeMap(exprMap);

	//this is brutal, needs to be replaced with a iterator
	for (i = 0; i < stacks.size(); i++)
	{	
		while (!stacks[i].empty())
		{
			delete stacks[i].top();
			stacks[i].pop();
		}
	}
	delete start;
}

