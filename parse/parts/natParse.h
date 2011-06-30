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
#include "tokParse.h"
#include "altParse.h"
#include "seqParse.h"
#include "../nodes/numNode.h"


class natParse : public parsePart
{
	protected:
		token *N0,*N1,*N2,*N3,*N4,*N5,*N6,*N7,*N8,*N9;
		altParse *N01,*N23,*N45,*N67,*N89,*N0123,*N4567,*N456789,*Nany;

	int getInt(std::string value)
	{
		int temp;
		std::stringstream buffer(value);
		buffer >> temp;
		return temp;
	}

	public:
	virtual void loadString(int offset, const std::string& data)
	{
		int i;
		int out = 0;
		seqParse NATStrip(Nany);
		NATStrip.loadString(offset,data);
		for (i=0; i < NATStrip.getTrees().size(); i++)
		{
			out = getInt(data.substr(offset,
				NATStrip.getTrees()[i].first - offset));
			succ.push_back( std::pair<int,eqnNode*>(
				NATStrip.getTrees()[i].first,
				new numNode(out)));
		}
	}

	natParse()
	{
		N0 = new token("0");
		N1 = new token("1");
		N2 = new token("2");
		N3 = new token("3");
		N4 = new token("4");
		N5 = new token("5");
		N6 = new token("6");
		N7 = new token("7");
		N8 = new token("8");
		N9 = new token("9");
		N01 = new altParse(N0,N1);
		N23 = new altParse(N2,N3);
		N45 = new altParse(N4,N5);
		N67 = new altParse(N6,N7);
		N89 = new altParse(N8,N9);
		N0123 = new altParse(N01,N23);
		N4567 = new altParse(N45,N67);
		N456789 = new altParse(N4567,N89);
		Nany = new altParse(N0123,N456789);
	}
};


#endif
