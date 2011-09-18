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
#ifndef NN_PARSERFULL_H
#define NN_PARSERFULL_H

#include "../parse/parts/expParse.h"
#include "../parse/parts/idParse.h"
#include "../parse/nodes/eqnNode.h"
#include "break-words.h"
#include <vector>
#include <map>
#include <utility>

/**
 * @class parserFull
 *
 * @brief The parser's user accessible side works through a single method getExpr(),
 *	which accepts a string as argument and returns a parse tree
 */

class parserFull
{
	protected:

	// void deleteList(std::vector<std::pair<int, eqnNode*> > list)
	/**	
	 * @brief Iterates over the provided list, freeing all memory from the 
	 * 	second element in each pair.
	 * @param list The vector containing memory to be freed
	 *
	 */
	static void deleteList(std::vector<std::pair<int, eqnNode*> > list);

	// void freeMap(std::map< std::pair<int, int>, std::vector<std::pair<int, eqnNode*> > > fails)
	/**
	 * @brief Iterates over the provided map, calling deleteList() on each element.
	 * @param fails The map containing memory to be freed
	 */
	static void freeMap(std::map< std::pair<int, int>, std::vector<std::pair<int, eqnNode*> > > fails);

	public:

	//eqnNode* getExpr(std::string input);
	/**
	 * @brief If the string, input, is syntactically correct, a parse tree 
	 *	is returned, otherwise a null pointer is returned.
	 * @param input The string to be parsed
	 * 
	 * @returns a parse tree representing the string input, 
	 *	or null if the parse fails
	 *
	 */
	static eqnNode* getExpr(const std::string& input);

	/**
	 * @brief parses a string, and returns a "nice" equivalent string
	 * @param input the string to convert
	 * @returns a "nice" string equivalent to the original
	 */
	static std::string makenice(const std::string& input);
};

#endif
