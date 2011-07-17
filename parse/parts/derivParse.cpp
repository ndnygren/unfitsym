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

#include "derivParse.h"
#include <string>

void derivParse::loadString(int offset, const std::string& data, int cap)
{
	unsigned int i;
	token leftt("\\frac{d");
	token centert("}{d");
	token rightt("}");
	token leftt2("\\frac{d}{d");
	token centert2("}");
	expParse cl;
	expParse cr;
	expParse cl2;
	parenParse cr2;
	cassetteMachine seq;
	cassetteMachine seq2;

	deleteAll();

	//parsing the "small" format: \frac{df(x)}{dx}
	seq.setMap(fails);
	seq.add(&leftt);
	seq.add(&cl);
	seq.add(&centert);
	seq.add(&cr);
	seq.add(&rightt);
	seq.loadString(offset,data,cap);


	for (i = 0; i< seq.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq.pieces[i].first, new derivNode(seq.pieces[i].second[1], seq.pieces[i].second[3])));
	}

	//parsing the "large" format: \frac{d}{dx}(f(x))
	seq2.setMap(fails);
	seq2.add(&leftt2);
	seq2.add(&cl2);
	seq2.add(&centert2);
	seq2.add(&cr2);
	seq2.loadString(offset,data,cap);

	for (i = 0; i< seq2.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq2.pieces[i].first, new derivNode(seq2.pieces[i].second[3], seq2.pieces[i].second[1])));
	}

}
