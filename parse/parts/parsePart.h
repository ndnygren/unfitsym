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
#ifndef NN_PARSEPART_H
#define NN_PARSEPART_H

#include <vector>
#include <map>
#include <utility>
#include "../nodes/eqnNode.h"

class parsePart 
{
	protected:
	std::vector<std::pair<int,eqnNode*> > succ;
	std::map< std::pair<int,int>, 
		std::vector<std::pair<int, eqnNode*> > > *fails;
	void deleteAll()
	{
		int i;
		for (i = 0; i < (int)succ.size(); i++)
			if (succ[i].second != 0)
				{ delete succ[i].second; }
		succ.clear();
	}

	void copySucc(std::vector<std::pair <int, eqnNode*> > list)
	{
		int i;
		
		for (i = 0; i < (int)list.size(); i++ )
		{ 
			succ.push_back(std::pair<int,eqnNode*>(
				list[i].first,
				list[i].second->copy())); 
		}
	}

	std::vector<std::pair<int,eqnNode*> > copyList(std::vector<std::pair<int, eqnNode*> > list)
	{
		int i;
		std::vector<std::pair<int,eqnNode*> > outlist;

		for (i = 0; i < (int)list.size(); i++ )
		{ 
			outlist.push_back(std::pair<int,eqnNode*>(
				list[i].first,
				list[i].second->copy())); 
		}
		return outlist;
	}

	public:
	void setMap( std::map< std::pair<int,int>, 
		std::vector<std::pair<int, eqnNode*> > > *f) { fails = f; }
	virtual void loadString(int offset, const std::string& data, int cap) = 0;
	std::vector<std::pair<int,eqnNode*> > getTrees() const 
		{ return succ; };

	virtual ~parsePart() { };
};

#endif