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

#include "intParse.h"
#include "../nodes/intBNode.h"
#include "dParse.h"
#include <string>

using namespace std;

void intParse::loadString(int offset, const std::string& data, int cap)
{
	unsigned int i;
	token leftt("\\int");
	token centert("d");
	token upt("^");
	token lowt("_");
	curlyParse upe;
	curlyParse lowe;
	expParse cl;
	dParse cr;
	cassetteMachine seq;
	cassetteMachine seq2;
	cassetteMachine seq3;

	deleteAll();


	//parsing indefinite integrals
	seq.setMap(fails);
	seq.add(&leftt);
	seq.add(&cl);
	seq.add(&cr);
	seq.loadString(offset,data,cap);


	for (i = 0; i< seq.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq.pieces[i].first, new intNode(seq.pieces[i].second[1], seq.pieces[i].second[2])));
	}

	// parsing definite integrals with the lower bound first
	seq2.setMap(fails);
	seq2.add(&leftt);
	seq2.add(&lowt);
	seq2.add(&lowe);
	seq2.add(&upt);
	seq2.add(&upe);
	seq2.add(&cl);
	seq2.add(&cr);
	seq2.loadString(offset,data,cap);

	for (i = 0; i< seq2.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq2.pieces[i].first, new intBNode(seq2.pieces[i].second[5], seq2.pieces[i].second[6], seq2.pieces[i].second[4], seq2.pieces[i].second[2])));
	}

	// parsing integrals with upper bound first
	seq3.setMap(fails);
	seq3.add(&leftt);
	seq3.add(&upt);
	seq3.add(&upe);
	seq3.add(&lowt);
	seq3.add(&lowe);
	seq3.add(&cl);
	seq3.add(&cr);
	seq3.loadString(offset,data,cap);

	for (i = 0; i< seq3.pieces.size(); i++)
	{
		succ.push_back(std::pair<int,eqnNode*>( seq3.pieces[i].first, new intBNode(seq3.pieces[i].second[5], seq3.pieces[i].second[6], seq3.pieces[i].second[2], seq3.pieces[i].second[4])));
	}
}
