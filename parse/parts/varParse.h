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
#ifndef NN_VARPARSE_H
#define NN_VARPARSE_H

#include <utility>
#include "multiTokParse.h"
#include "../nodes/varNode.h"


/**
 * @class varParse
 *
 * @brief Parses single letter variables. 
 */

class varParse : public parsePart
{
	public:
	virtual void loadString(int offset, const std::string& data, int cap)
	{
		int i;
		std::string out;
		multiTokParse digits;

		digits.add("a"); digits.add("b"); digits.add("c");
//		digits.add("d"); // will be used fo calculus;
		digits.add("e"); digits.add("f"); digits.add("g");
		digits.add("h"); digits.add("i"); digits.add("j");
		digits.add("k"); digits.add("l"); digits.add("m");
		digits.add("n"); digits.add("o"); digits.add("p");
		digits.add("q"); digits.add("r"); digits.add("s");
		digits.add("t"); digits.add("u"); digits.add("v");
		digits.add("w"); digits.add("x"); digits.add("y");
		digits.add("z"); digits.add("C"); 

		digits.add("\\pi"); digits.add("\\phi"); 

		deleteAll();
		if (offset < (int)data.length() - cap)
		{
			digits.loadString(offset,data,cap);
			for (i=0; i < (int)digits.getTrees().size(); i++)
			{
				out = data.substr(offset, digits.getTrees()[i].first - offset);
				succ.push_back( std::pair<int,eqnNode*>(
					digits.getTrees()[i].first,
					new varNode(out)));
			}
		}
	}

	varParse()
	{
	}

	virtual ~varParse() 
	{
		deleteAll();
	}
};


#endif
