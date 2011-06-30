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
#ifndef NN_MULTITOKENPARSE_H
#define NN_MULTITOKENPARSE_H

#include "parsePart.h"
#include <string>

class multiTokParse : public parsePart
{
	protected:
	std::vector<std::string> str;

	public:
	void loadString(int offset, const std::string& data, int cap)
	{
		int i;
		deleteAll();
		for (i = 0; i < (int)str.size(); i++)
		{
			if (offset < (int)data.length() - cap)
			{
				if (data.substr(offset, str[i].length()) == str[i])
				{
					succ.push_back(std::pair<int,eqnNode*>
							(offset + str[i].length(), 0));
				}
			}
		}
	}

	void add(std::string input) { str.push_back(input); }
	multiTokParse(std::string input) { str.push_back(input); }
	multiTokParse() { }
	virtual ~multiTokParse() { deleteAll(); }
};

#endif
