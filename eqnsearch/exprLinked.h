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
#ifndef NN_EXPRLINKED_H
#define NN_EXPRLINKED_H

#include <vector>
#include "exprHolder.h"
#include "exprMetric.h"
#include "../parse/nodes/eqnNode.h"


class exprLinked : exprHolder
{
	protected:
	eqnNode* expr;

	public:
	std::vector<eqnNode*> changes;
	int id;

	virtual std::string str() const;
	void load();

	exprLinked();
	exprLinked(eqnNode* input);
	exprLinked(eqnNode* input, int id);
	exprLinked(const exprLinked& old);
	virtual ~exprLinked();

	bool operator< (const exprLinked& rhs) const;
	bool operator> (const exprLinked& rhs) const;
	
};

#endif