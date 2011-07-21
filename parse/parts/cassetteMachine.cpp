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
	//for all parseParts except the last in sequence, the cap is changed
	//	reduce the string size by one
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
		// do not try to copy null pointers
		if (list[i].second == 0)
		{
			outlist.push_back(std::pair<int,eqnNode*>(list[i].first,0)); 
		}
		// create of copy of any real parse tree
		else
		{ 
			outlist.push_back(std::pair<int,eqnNode*>( list[i].first, list[i].second->copy())); 
		}
	}
	return outlist;
}


void cassetteMachine::popAndFree()
{
	std::vector<std::pair <int, eqnNode*> > toplist = cassette.back().second; 

	int i;
	for (i = 0; i < (int)toplist.size(); i++)
		if (toplist[i].second != 0)
			{ delete toplist[i].second; }
	toplist.clear();

	cassette.pop_back();
}

void cassetteMachine::collectSuccess() 
{
	unsigned int i;
	int last;
	eqnNode* temp;
	vector<eqnNode*> comp;

	for (i = 0; i < cassette.size(); i++)
	{
		// cassette=stack.
		// iterate over the cassette and collect one parse tree 
		// 	from each parsePart
		temp = cassette[i].second[cassette[i].first].second;
		if (temp == 0) { comp.push_back(0); }
		else { comp.push_back(temp->copy()); }
	}
	//the offset to be collected is the same as the offset of the success
	//	of the parsePart at the top of the stack.
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
	// the offset of the "current" index of the top succ list on the stack
	return cassette.back().second[cassette.back().first].first;
}

pair<int,vector<pair<int,eqnNode*> > > cassetteMachine::makeCMP(parsePart* input) const
{
	// makes a copy, then pairs it with an int=0(the index of the new list)
	return pair<int,vector<pair<int,eqnNode*> > >(0,copySucc(input->getTrees()));
}

void cassetteMachine::add(parsePart* input)
{
	// passes the parse cache
	input->setMap(fails);
	// adds the new parsePart
	partlist.push_back(input);
}

void cassetteMachine:: loadString(int offset, const string& data, int cap)
{
	parsePart* current;
	assert(partlist.size() > 0);

	// this should be unneccessary, but here incase the same cassette is called twice
	cassette.clear();

	// initialize the cassette
	partlist[0]->loadString(offset, data, cap + goodCap());
	cassette.push_back(makeCMP(partlist[0]));

	while (cassette.size() > 0)
	{
		if (endOfSucc())
		{
			// when all successes have been considered, retreat one 
			//	layer and move to the next success at that layer
			popAndFree();
			if (cassette.size() > 0)
				{ cassette.back().first++; }
		}
		else if (cassette.size() < partlist.size())
		{
			// if some parseParts have not been called,
			// 	move a layer deeper
			current = partlist[cassette.size()];
			current->loadString(currentOffset(), data, cap + goodCap());
			cassette.push_back(makeCMP(current));
		}
		else // (cassette.size() == partlist.size()) with any luck;
		{
			// at the final parsePart, collect the successfull sequence
			collectSuccess();
			cassette.back().first++; 
		}
	}
}

cassetteMachine::~cassetteMachine()
{
	unsigned int i,j;

	for (i = 0; i < pieces.size(); i++)
	{
		for (j = 0; j < pieces[i].second.size(); j++)
		{
			if (pieces[i].second[j] != 0)
			{
				delete pieces[i].second[j];
			}
		}
		pieces[i].second.clear();
	}
}
