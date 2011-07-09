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
#ifndef NN_ALTPARSE_H
#define NN_ALTPARSE_H

#include "parsePart.h"
#include <string>
#include <iostream>

class altParse : public parsePart
{
	protected:
	parsePart* left;
	parsePart* right;	

	public:
	void loadString(int offset, const std::string& data, int cap)
	{
		int i;

		deleteAll();

		if (offset < (int)data.length() - cap)
		{
			left->loadString(offset,data,cap);
			right->loadString(offset,data,cap);

			for (i = 0; i < (int)left->getTrees().size(); i++ )
				{ succ.push_back(left->getTrees()[i]); }
			for ( i = 0; i < (int)right->getTrees().size(); i++)
				{ succ.push_back(right->getTrees()[i]); }
		}
	}

	altParse(parsePart* lin, parsePart* rin)
	{
		left = lin;
		right = rin;
	}
	
	virtual ~altParse() { deleteAll(); }
};


#endif