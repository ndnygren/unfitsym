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

#include "fracParse.h"
#include <string>

void fracParse::loadString(int offset, const std::string& data, int cap)
{
	int i,k;
	expParse lefte;
	expParse righte;
	token leftt("\\frac{");
	token centert("}{");
	token rightt("}");

	lefte.setMap(fails);
	righte.setMap(fails);

	leftt.loadString(offset,data,cap);
	if (leftt.getTrees().size() > 0)
	{
		lefte.loadString(leftt.getTrees()[0].first,data,cap+1);
		for (i = 0; i < (int)lefte.getTrees().size(); i++)
		{
			centert.loadString(lefte.getTrees()[0].first, data, cap);
			if( (int)centert.getTrees().size() > 0)
			{
				righte.loadString(centert.getTrees()[0].first, data, cap);
				for (k = 0; k < (int)righte.getTrees().size(); k++)
				{
					rightt.loadString(righte.getTrees()[k].first,data,cap);
					if (rightt.getTrees().size()>0)
					{
					succ.push_back(std::pair<int,eqnNode*>(
						rightt.getTrees()[0].first,
						new fracNode(
						lefte.getTrees()[i].second,
						righte.getTrees()[k].second)));
						
					}
				}
			}		
		}
	}
}
