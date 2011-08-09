
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


/**
 * @class eqnComp
 *
 * @brief A class which satisfies the STL piority_queue Compare template. eqnComp
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


/**
 * @class searchMaxMin
 *
 * @brief the search engine applies a set of standard modifications to each expression,
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
	void freeMap(std::map<std::string, eqnNode*> &inmap);

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

	// the original stack was replaced with many priority queues, converting
	// 	the depth-first search into a best-first search
	std::vector<std::priority_queue<eqnNode*, std::vector<eqnNode*>, eqnComp> > stacks;

	/*
	 * void allPush(eqnNode*)
	 *
	 * pushes the supplied expression to all priority queues
	 */
	void allPush(eqnNode* input);
	

	/*
	 * searchMaxMin(eqnNode* input, eqnMetric* inrate)
	 *
	 * initializes the search and performs a shallow first look.
	 */
	searchMaxMin(eqnNode* input, eqnMetric* inrate);

	/*
	 * void addNewDirection(eqnMetric* inrate);
	 *
	 * adds an additional direction for a multi-directional search
	 */
	void addNewDirection(eqnMetric* inrate);

	/*
	 * void addToMap(std::string from, eqnNode *newnode)
	 *
	 * Checks if the new expression has been previously discovered,
	 * 	adds the pair to the adjPair list.
	 */
	void addToMap(std::string from, eqnNode *newnode);

	/*
	 * void next(int limit = 100)
	 *
	 * Search proceeds from its previous position until a number(limit)
	 * 	of new expressions have been evaluated, and their subsequent 
	 * 	expressions added to the queue.
	 */
	void next(int limit = 1000);

	/*
	 * vector<eqnNode*> best(unsigned int limit = 10)
	 *
	 * iterating over the map, the best(least by some metric) expressions
	 *	are returned, the calling function may decide that one of them
	 *	is the proof goal.
	 */
	std::vector<eqnNode*> best(unsigned int limit = 10);

	~searchMaxMin();
};

#endif
