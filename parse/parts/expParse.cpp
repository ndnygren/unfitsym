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
#include "expParse.h"

void expParse::loadString(int offset, const std::string& data, int cap)
{
	int i;
	natParse number;
	sumParse sums;

	if (offset < data.size() - cap)
	{
		number.loadString(offset, data, cap);
		for (i = 0; i < number.getTrees().size(); i++ )
			{ succ.push_back(number.getTrees()[i]); }

		sums.loadString(offset, data, cap);
		for (i = 0; i < sums.getTrees().size(); i++ )
			{ succ.push_back(sums.getTrees()[i]); }
	}
}
