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
 * @file break-words.h
 *
 * @brief a collection of methods used to remove whitespace
 */

/*
 * bool n_alpha(char t)
 *
 * returns true if t is an alphabetic character
 */
bool n_alpha(char t);

/*
 * bool n_num(char t)
 *
 * returns true if t is an numeric character
 */
bool n_num(char t);

/*
 * bool n_oper(char t)
 *
 * returns true if t is an operator character
 */
bool n_oper(char t);

/*
 * bool nlrsqb(char t)
 *
 * returns true if t is not a square bracket
 */
bool nlrsqb(char t);

/*
 * bool lrsqb(char t)
 *
 * returns true if t is a square bracket
 */
bool lrsqb(char t);

/*
 * bool w_only(char t)
 *
 * returns true if t is whitespace
 */
bool w_only(char t);
/*
 * bool w_only(char t)
 *
 * returns true if t is whitespace or a comma
 */
bool w_commas(char t);

/*
 * string stripwhite(string input, bool (*whitespc)(char))
 *
 * removes every character that satisfies the supplied function *whitespc
 */
std::string stripwhite(const std::string& input, bool (*whitespc)(char));

/*
 * vector<string> breakwords(string input, bool (*whitespc)(char));
 *
 * breaks the string on all points where the funstion *whitespace is satisfied
 */
std::vector<std::string> breakwords(const std::string& input, bool (*whitespc)(char));


#endif

