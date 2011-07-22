
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

#ifndef NN_SEARCHMAXMIN_H
#define NN_SEARCHMAXMIN_H

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

/*
 * class eqnComp
 *
 * A class which satisfies the STL piority_queue Compare template. eqnComp
 *	varies the order base on the metric that it is supplied
 */

class eqnComp
{
	protected:
	// a mapping onto the integers that will be used to order expressions
	eqnMetric *rate;

	public:
	// STL priority_queue calls this function
	bool operator() (const eqnNode* lhs, const eqnNode* rhs)
	{
		return rate->score(lhs) > rate->score(rhs);
	}

	eqnComp() { }
	
	eqnComp(eqnMetric* input)
		{ rate = input; }
};


/*
 * class searchMaxMin
 *
 * the search engine applies a set of standard modifications to each expression,
 * 	generating a graph of equivilant expressions. Each path in this graph
 *	represents a proof of the end expression, by the start expression.
 */
class searchMaxMin
{
	protected:
	eqnComp comp;
	// this rate should always be the same as above
	eqnMetric *rate;
	

	/*
	 * void freeMap(std::map<std::string, eqnNode*> &inmap)
	 * 
	 * iterates over the map and frees all memory used by the eqnNode*s
	 */
	void freeMap(std::map<std::string, eqnNode*> &inmap)
	{
		std::map<std::string, eqnNode*>::iterator it;

		for (it=inmap.begin(); it!=inmap.end(); it++)
			{ delete (*it).second; }
	}

	public:
	//TODO: consider getter functions for these

	// a copy of the original expression
	eqnNode* start;

	// the graph is described here, each edge as a 
	//	pair=(from string, to string)
	std::vector<std::pair<std::string, std::string> > adjPairs;

	// a reverse map strings -> parse trees, this is faster than parsing
	//	a second time.
	std::map<std::string, eqnNode*> exprMap;

	// the original stack was replaced with a priority queue, converting
	// 	the depth-first search into a best-first search
	std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp> stack;

	/*
	 * searchMaxMin(eqnNode* input, eqnMetric* inrate)
	 *
	 * initializes the search and performs a shallow first look.
	 */
	searchMaxMin(eqnNode* input, eqnMetric* inrate)
	{
		rate = inrate; 
		comp = eqnComp(rate);
		// the proiority_queue is initialized with the supplied metric here
		stack = std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp>(comp);
		// a first value is entered into the search
		start = input->copy();
		stack.push(input->copy());
	
		next();
	}

	/*
	 * void next(int limit = 100)
	 *
	 * Search proceeds from its previous position until a number(limit)
	 * 	of new expressions have been evaluated, and their subsequent 
	 * 	expressions added to the queue.
	 */
	void next(int limit = 100)
	{
		unsigned int i;
		int count = 0;

		// exprLinked interacts with the expression manipulators 
		//	(stored in eqnsearch/alter/)
		// 	and returns a list of expressions to add to the adjacent
		//	pairs list
		exprLinked* current;

		// the stack should never empty itself, but this is left in
		// 	in case the rules about identity (+0, *1) are removed.
		while (stack.size() > 0 && count < limit)
		{
			current = new exprLinked(stack.top());
			delete stack.top();
			stack.pop();
//			cout << current[0].str() << "\n";

			// load() generates fresh candidates from the current 
			// expression
			current[0].load();

			for(i = 0; i < current[0].changes.size(); i++)
			{
				// if it already exists, we only add the new path
				if (exprMap.count(current[0].changes[i]->str()) > 0)
				{
					adjPairs.push_back( std::pair<std::string,std::string> (current[0].str(), current[0].changes[i]->str()));
				}
				else // otherwise it is new discovery
				{
					exprMap[current[0].changes[i]->str()] = current[0].changes[i]->copy();
					adjPairs.push_back( std::pair<std::string,std::string> (current[0].str(), current[0].changes[i]->str()));
					//it is added to the stack to be evaluated itself
					stack.push(current[0].changes[i]->copy());
					count++;
				}
			}
			delete current;
		}
	}

	/*
	 * vector<eqnNode*> best(unsigned int limit = 10)
	 *
	 * iterating over the map, the best(least by some metric) expressions
	 *	are returned, the calling function may decide that one of them
	 *	is the proof goal.
	 */
	std::vector<eqnNode*> best(unsigned int limit = 10)
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

#endif
