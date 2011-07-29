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

#include "cosineParse.h"
#include <string>

void cosineParse::loadString(int offset, const std::string& data, int cap)
{
	unsigned int i;
	token fn("\\cos");
	parenParse righte;
	cassetteMachine seq;

	deleteAll();

	seq.setMap(fails);
	seq.add(&fn);
	seq.add(&righte);
	seq.loadString(offset,data,cap);

	for (i = 0; i< seq.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq.pieces[i].first, new cosineNode(seq.pieces[i].second[1])));
	}
}
