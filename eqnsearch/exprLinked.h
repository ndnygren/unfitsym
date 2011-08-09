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
#include "eqnMetric.h"
#include "../parse/nodes/eqnNode.h"

/**
 * @class exprLinked
 *
 * @brief Holder for expressions, generates candidate solutions and handles 
 * some memory allocation.
 *
 */

class exprLinked 
{
	protected:
	/**
	 * @brief the current expression
	 */
	eqnNode* expr;

	public:
	/**
	 * @brief The new expressions found by single manipulations of the current expression.
	 */
	std::vector<eqnNode*> changes;

	/**
	 * @brief passes the str() call to the current eqnNode*
	 * @return passes back return value from the inner expression
	 */
	virtual std::string str() const;
	/**
	 * @brief calls alterExpression::getCand() and loads the changes list
	 */
	void load();

	exprLinked();
	exprLinked(eqnNode* input);
	exprLinked(const exprLinked& old);
	virtual ~exprLinked();
};

#endif
