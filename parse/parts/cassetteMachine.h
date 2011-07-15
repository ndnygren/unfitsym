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

#ifndef NN_CASSMACH_H
#define NN_CASSMACH_H

#include <vector>
#include "parsePart.h"

class cassetteMachine
{
	protected:
	std::vector<parsePart*> partlist;
	std::vector<std::pair<int, std::vector<std::pair<int,eqnNode*> > > > cassette;
	std::vector<std::pair<int,std::vector<eqnNode*> > > pieces;
	std::map< std::pair<int,int>, std::vector<std::pair<int, eqnNode*> > > *fails;

	int goodCap() const;
	std::vector<std::pair <int, eqnNode*> > copySucc(const std::vector<std::pair <int, eqnNode*> > &list) const;
	void collectSuccess(); 
	bool endOfSucc() const;
	int currentOffset () const;
	std::pair<int,std::vector<std::pair<int,eqnNode*> > > makeCMP(parsePart* input) const;
	
	public:
	void setMap( std::map< std::pair<int,int>, std::vector<std::pair<int, eqnNode*> > > *f) { fails = f; }
	void add(parsePart* input);
	void loadString(int offset, const std::string& data, int cap);
	
};


#endif
