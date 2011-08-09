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
#ifndef NN_TOKENPARSE_H
#define NN_TOKENPARSE_H

#include "parsePart.h"
#include <string>

/**
 * @class token
 *
 * @brief The primative parsePart used by all others, identifies and 
 *	comsumes characters.
 */
class token : public parsePart
{
	protected:
	/**
	 * @brief The string value to test against while parsing
	 */
	std::string str;

	public:
	void loadString(int offset, const std::string& data, int cap)
	{
		deleteAll();
		if (offset < (int)data.length() - cap)
		{
			//success whenever the string exists
			if (data.substr(offset, str.length()) == str)
			{
				// returns a meaningfull new offset,
				// 	but a null pointer for parse tree
				succ.push_back(std::pair<int,eqnNode*>
						(offset + str.length(), (eqnNode*)0));
			}
		}
	}

	token(std::string input) { str = input; }
	virtual ~token() { deleteAll(); }
};

#endif
