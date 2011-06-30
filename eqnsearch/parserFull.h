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
#ifndef NN_PARSERFULL_H
#define NN_PARSERFULL_H

#include "../parse/parts/expParse.h"
#include "../parse/nodes/eqnNode.h"
#include <vector>
#include <map>
#include <utility>

class parserFull
{
	protected:
	std::map< std::pair<int, int>, std::vector<std::pair<int, eqnNode*> > > fails;

	void deleteList(std::vector<std::pair<int, eqnNode*> > list);
	void freeMap(std::map< std::pair<int, int>, std::vector<std::pair<int, eqnNode*> > > fails);

	public:
	eqnNode* getExpr(std::string input);
	~parserFull();
};

#endif
