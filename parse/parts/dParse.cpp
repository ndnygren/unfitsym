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

#include "dParse.h"
#include <string>

void dParse::loadString(int offset, const std::string& data, int cap)
{
	unsigned int i;
	token lp("{");
	token d("d");
	expParse ex;
	token rp("}");
	cassetteMachine seq1;
	cassetteMachine seq2;

	deleteAll();

	seq1.setMap(fails);
	seq1.add(&lp);
	seq1.add(&d);
	seq1.add(&ex);
	seq1.add(&rp);
	seq1.loadString(offset,data,cap);
	
	for (i = 0; i< seq1.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq1.pieces[i].first, seq1.pieces[i].second[2]->copy()));
	}

	seq2.setMap(fails);
	seq2.add(&d);
	seq2.add(&lp);
	seq2.add(&ex);
	seq2.add(&rp);
	seq2.loadString(offset,data,cap);
	
	for (i = 0; i< seq2.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq2.pieces[i].first, seq2.pieces[i].second[2]->copy()));
	}

}
