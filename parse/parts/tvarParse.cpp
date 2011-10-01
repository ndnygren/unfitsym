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

#include "tvarParse.h"
#include <string>

void tvarParse::loadString(int offset, const std::string& data, int cap)
{
	unsigned int i;
	token op1("TV_{");
	natParse cr;
	token op2("}");
	cassetteMachine seq;

	seq.setMap(fails);
	seq.add(&op1);
	seq.add(&cr);
	seq.add(&op2);
	seq.loadString(offset,data,cap);

	for (i = 0; i< seq.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq.pieces[i].first, new tvarNode(seq.pieces[i].second[1])));
	}
}
