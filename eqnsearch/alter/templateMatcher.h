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

#include <utility>
#include <vector>
#include <string>
#include "../../parse/parserFull.h"

#ifndef NN_TEMPLATEMATCHER_H
#define NN_TEMPLATEMATCHER_H

class templateMatcher
{
	protected: 
	/**
	 * @brief the list of rules to apply to each expression.
	 */
	static std::vector<std::pair<eqnNode*, eqnNode*> > rulelist;

	/**
	 * @brief Sorts a list of template variable definitions.
	 * @param The list to be sorted.
	 */
	static void varDefSort(std::vector<std::pair<int, eqnNode*> >& defs);

	/**
	 * @brief Removes duplicates from a list of template variable definitions.
	 * @param The list to be modified.
	 */
	static void varDefDup(std::vector<std::pair<int, eqnNode*> >& defs);

	/**
	 * @brief Checks a list of template variable definitions and ensures that if duplicates exist, they are all equal.
	 * @param The list to be validated.
	 */
	static bool varDefValidate(const std::vector<std::pair<int, eqnNode*> >& defs);

	/**
	 * @brief Frees all memory in a list of template variable definitions.
	 * @param The list to be freed.
	 */
	static void varDefFree(std::vector<std::pair<int, eqnNode*> >& defs);

	/**
	 * @brief using a list of template variable definitions, fills a pattern
	 *	to create a fully defined expression
	 * @param defs The list of template variable definitions
	 * @param outpat the output pattern
	 * @returns an expression formed from the given pattern by substituting in the definitions.
	 */
	static eqnNode* fillPattern( const std::vector<std::pair<int, eqnNode*> >& defs, eqnNode* outpat);
	public:

	/**
	 * @brief Read all rules and allocate memory
	 */
	static void init();

	/**
	 * @brief Deallocate memory in static members (rulelist)
	 */
	static void end();

	/**
	 * @brief Parses and if valid, adds a new rule to the list
	 * @param input the string to be parsed and added
	 */
	static void addRule(const std::string& input);

	/**
	 * @brief compares the input to each item in the rule list
	 * @param input the expression to be compared
	 * @returns A list of equivalent expressions generated from which ever rules do apply.
	 */
	static std::vector<eqnNode*> getMatches(const eqnNode* input);
};

#endif
