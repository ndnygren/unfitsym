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
#ifndef NN_NATPARSE_H
#define NN_NATPARSE_H

#include <sstream>
#include <utility>
#include "multiTokParse.h"
#include "seqParse.h"
#include "../nodes/numNode.h"


/*
 * class natParse
 * 
 * parses a string of digits, {0,...,9} returns numNodes on success
 */
class natParse : public parsePart
{
	protected:
	/*
	 * int getInt(std::string value)
	 *
	 * uses string streams to parse ints from strings;
	 */
	int getInt(std::string value)
	{
		int temp;
		std::stringstream buffer(value);
		buffer >> temp;
		return temp;
	}

	public:
	virtual void loadString(int offset, const std::string& data, int cap)
	{
		int i;
		int out = 0;
		multiTokParse digits;
		digits.add("1");
		digits.add("2"); //adds all digits to the multiTok
		digits.add("3");
		digits.add("4");
		digits.add("5");
		digits.add("6");
		digits.add("7");
		digits.add("8");
		digits.add("9");
		digits.add("0");
		seqParse NATStrip(&digits);
		deleteAll(); // clears the existing succ list
		if (offset < (int)data.length() - cap)
		{
			NATStrip.loadString(offset,data,cap);
			for (i=0; i < (int)NATStrip.getTrees().size(); i++)
			{
				out = getInt(data.substr(offset,
					NATStrip.getTrees()[i].first - offset));
				succ.push_back( std::pair<int,eqnNode*>(
					NATStrip.getTrees()[i].first,
					new numNode(out)));
			}
		}
	}

	natParse()
	{
	}

	virtual ~natParse() 
	{
		deleteAll();
	}
};


#endif
