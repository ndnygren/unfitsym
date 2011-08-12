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
#include "exprLinked.h"
#include "alter/alterExpression.h"

using namespace std;

std::string exprLinked::str() const
{ 
	if (expr != 0) { return expr->str(); }
	else { return "zero"; }
}

void exprLinked::load()
{
	unsigned int i;
	alterExpression::copyCand(alterExpression::getCand(expr), changes);

	for (i = 0; i < changes.size(); i++)
	{
		alterExpression::replaceIndex(changes[i]);
	}
}

exprLinked::exprLinked()
{
	expr = 0; 
}

exprLinked::exprLinked(eqnNode* input)
{
	expr = input->copy();
}

exprLinked::exprLinked(const exprLinked& old)
{
	if (old.expr != 0)
		{ expr = old.expr->copy(); }
	else
		{ expr = 0; }
}


exprLinked::~exprLinked()
{
	if (expr != 0)
	{
		delete expr;
	}
	alterExpression::freeCand(changes);
	changes.clear();
}
