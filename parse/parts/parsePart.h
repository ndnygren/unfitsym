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
#ifndef NN_PARSEPART_H
#define NN_PARSEPART_H

#include <vector>
#include <map>
#include <utility>
#include "../nodes/eqnNode.h"

/**
 * @class parsePart 
 *
 * @brief The interface for all types of parser components. There is one for each 
 *	node type, and one node types for each expression type in the CFG.
 */
class parsePart 
{
	protected:
	/**
	 * @brief list of successful parses
	 * @details pairs of successful parses, the int represents the 
	 *	number of characters "consumed" so far, and therefore where 
	 *	the subsequent parsePart should begin reading.
	 *	the eqnNode* is the parse tree returned from the parsePart,
	 *	it may be null in the case of tokens
	 */
	std::vector<std::pair<int,eqnNode*> > succ;

	/**
	 * @brief the cache of previous parses, passed down when recursing
	 */
	std::map< std::pair<int,int>, std::vector<std::pair<int, eqnNode*> > > *fails;

	// void deleteAll()
	/**
	 * @brief frees all memory contained in the succ list. If this data is needed,
	 * it must be copied prior to freeing the parse part containing it.
	 *
	 */
	virtual void deleteAll()
	{
		int i;
		for (i = 0; i < (int)succ.size(); i++)
			if (succ[i].second != 0)
				{ delete succ[i].second; }
		succ.clear();
	}

	// void copySucc(std::vector<std::pair <int, eqnNode*> > list)
	/**
	 * @brief pulls all elements of another parsePart's succ list, so that the 
	 * other parsePart may be safely deleted without losing the data.
	 *
	 * @param list The source list, to be copied
	 */
	void copySucc(std::vector<std::pair <int, eqnNode*> > list)
	{
		int i;
		
		for (i = 0; i < (int)list.size(); i++ )
		{ 
			if (list[i].second != 0)
			{ 
				succ.push_back(std::pair<int,eqnNode*>(
					list[i].first,
					list[i].second->copy())); 
			}
			else
			{
				succ.push_back(std::pair<int,eqnNode*>(
					list[i].first,
					(eqnNode*)0));
			}
		}
	}

	// std::vector<std::pair<int,eqnNode*> > copyList(std::vector<std::pair<int, eqnNode*> > list)
	/**
	 * @brief creates a copy of another parsePart's succ list, so that the 
	 * other parsePart may be safely deleted without losing the data.
	 *
	 * @param list The source list, to be copied
	 * @returns An identical list, in newly allocated memory
	 */
	std::vector<std::pair<int,eqnNode*> > copyList(std::vector<std::pair<int, eqnNode*> > list)
	{
		int i;
		std::vector<std::pair<int,eqnNode*> > outlist;

		for (i = 0; i < (int)list.size(); i++ )
		{ 
			outlist.push_back(std::pair<int,eqnNode*>(
				list[i].first,
				list[i].second->copy())); 
		}
		return outlist;
	}

	public:
	// void setMap( std::map< std::pair<int,int>, std::vector<std::pair<int, eqnNode*> > > *f)
	/**
	 * @brief Assigns the parse cache to the supplied pointer
	 * @param f The existing cache, to be shared 
	 */
	virtual void setMap( std::map< std::pair<int,int>, 
		std::vector<std::pair<int, eqnNode*> > > *f) { fails = f; }

	// virtual void loadString(int offset, const std::string& data, int cap)
	/**
	 *
	 * @param offset the number of characters in the string which have been 
	 *	"consumed" so far
	 * @param data the string to be parsed
	 * @param cap an upper bound on the string to be parsed, when recursing
	 *	into the first parsePart in a sequence, the cap is increased 
	 *	by 1, reducing the string size. This prevents infinite recursion.
	 * 
	 * @brief This is the function which initiates parsing. 
	 * @details It recurses into other
	 * parseParts, according to the CFG and returns a list of successes.
	 * These successes are composed of a pair, and integer representing 
	 * the number of characters consumed to reach this success, and a 
	 * parse tree, generated from the characters consumed. 
	 */
	virtual void loadString(int offset, const std::string& data, int cap) = 0;

	// std::vector<std::pair<int,eqnNode*> > getTrees()
	/**
	 * @brief Simple getter, allows access to the successes.
	 * @returns the vector of successes
	 */
	std::vector<std::pair<int,eqnNode*> > getTrees() const 
		{ return succ; };

	virtual ~parsePart() { };
};

#endif
