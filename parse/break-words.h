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


#ifndef NN_BREAKWORDS_H
#define NN_BREAKWORDS_H

#include <string>
#include <vector>

/**
 * @class break-words.h
 *
 * @brief Static functions, methods used to remove whitespace
 */

class breakWords
{
	public:
	// bool n_alpha(char t)
	/**
	 * @param t the character value to be tested
	 * @returns true if t is an alphabetic character
	 *
	 */
	static bool n_alpha(char t);

	// bool n_num(char t)
	/**
	 *
	 * @param t the character value to be tested
	 * @returns true if t is an numeric character
	 */
	static bool n_num(char t);

	// bool n_oper(char t)
	/**
	 *
	 * @param t the character value to be tested
	 * @returns true if t is an operator character
	 */
	static bool n_oper(char t);

	// bool nlrsqb(char t)
	/**
	 *
	 * @param t the character value to be tested
	 * @returns true if t is not a square bracket
	 */
	static bool nlrsqb(char t);

	// bool lrsqb(char t)
	/**
	 *
	 * @param t the character value to be tested
	 * @returns true if t is a square bracket
	 */
	static bool lrsqb(char t);

	// bool w_only(char t)
	/**
	 *
	 * @param t the character value to be tested
	 * @returns true if t is whitespace
	 */
	static bool w_only(char t);

	// bool w_only(char t)
	/**
	 *
	 * @param t the character value to be tested
	 * @returns true if t is whitespace or a comma
	 */
	static bool w_commas(char t);

	// string stripwhite(string input, bool (*whitespc)(char))
	/**
	 * @brief removes every character that satisfies the supplied function *whitespc
	 * @param input The string which will have whitespace removed
	 * @param whitespc the pointer to the function which decides what is whitespace
	 * @returns a new string, without whitespace
	 */
	static std::string stripwhite(const std::string& input, bool (*whitespc)(char));

	// vector<string> breakwords(string input, bool (*whitespc)(char));
	/**
	 * @brief breaks the string on all points where the funstion *whitespace is satisfied
	 * 
	 * @param input The string which will be broken at whitespace 
	 * @param whitespc the pointer to the function which decides what is whitespace
	 *
	 * @returns a vector of strings, all non-whitespace peices of input
	 *
	 */
	static std::vector<std::string> breakwords(const std::string& input, bool (*whitespc)(char));
};

#endif

