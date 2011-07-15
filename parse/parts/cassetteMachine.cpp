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


#include "cassetteMachine.h"
#include <cassert>

using namespace std;

int cassetteMachine::goodCap() const
{
	if (partlist.size() - cassette.size() > 1)
		{ return 1; }
	return 0;
}

std::vector<std::pair <int, eqnNode*> > cassetteMachine::copySucc(const std::vector<std::pair <int, eqnNode*> > &list) const
{
	int i;
	std::vector<std::pair <int, eqnNode*> > outlist; 
	
	for (i = 0; i < (int)list.size(); i++ )
	{ 
		if (list[i].second == 0)
		{
			outlist.push_back(std::pair<int,eqnNode*>(list[i].first,0)); 
		}
		else
		{ 
			outlist.push_back(std::pair<int,eqnNode*>( list[i].first, list[i].second->copy())); 
		}
	}
	return outlist;
}

void cassetteMachine::collectSuccess() 
{
	unsigned int i;
	int last;
	eqnNode* temp;
	vector<eqnNode*> comp;

	for (i = 0; i < cassette.size(); i++)
	{
		temp = cassette[i].second[cassette[i].first].second;
		if (temp == 0) { comp.push_back(0); }
		else { comp.push_back(temp->copy()); }
	}
	last = cassette[i-1].second[cassette[i-1].first].first;
	pieces.push_back(pair<int,vector<eqnNode*> >(last, comp));
}

bool cassetteMachine::endOfSucc() const
{
	if (cassette.back().first < (int)cassette.back().second.size())
		{ return false; }
	return true;
}
	
int cassetteMachine::currentOffset () const
{
	return cassette.back().second[cassette.back().first].first;
}

pair<int,vector<pair<int,eqnNode*> > > cassetteMachine::makeCMP(parsePart* input) const
{
	
	return pair<int,vector<pair<int,eqnNode*> > >(0,copySucc(input->getTrees()));
}

void cassetteMachine::add(parsePart* input)
{
	input->setMap(fails);
	partlist.push_back(input);
}

void cassetteMachine:: loadString(int offset, const string& data, int cap)
{
	parsePart* current;
	assert(partlist.size() > 0);

	cassette.clear();

	partlist[0]->loadString(offset, data, cap + goodCap());
	cassette.push_back(makeCMP(partlist[0]));

	while (cassette.size() > 0)
	{
		if (endOfSucc())
		{
			cassette.pop_back();
			if (cassette.size() > 0)
				{ cassette.back().first++; }
		}
		else if (cassette.size() < partlist.size())
		{
			current = partlist[cassette.size()];
			current->loadString(currentOffset(), data, cap + goodCap());
			cassette.push_back(makeCMP(current));
		}
		else // (cassette.size() == partlist.size()) with any luck;
		{
			collectSuccess();
			cassette.back().first++; 
		}
	}
}
