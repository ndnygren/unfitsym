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

class token : public parsePart
{
	protected:
	std::string str;

	public:
	void loadString(int offset, const std::string& data)
	{
		succ.clear();
		if (data.substr(offset, str.length()) == str)
		{
			succ.push_back(std::pair<int,eqnNode*>
					(offset + str.length(), 0));
		}
		else
			{ succ.clear(); }
	}

	token(std::string input) { str = input; };
};

#endif
