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
#ifndef NN_UNCHAINMETRIC_H
#define NN_UNCHAINMETRIC_H

#include "../parse/nodes/eqnNode.h"
#include "../parse/nodes/nodeTypes.h"
#include "eqnMetric.h"
#include <string>

/**
 * @class unchainMetric
 *
 *
 * @brief Metric to encourage the formation of derivatives from more simple functions
 *
 */

class unchainMetric : public eqnMetric
{
	public:

	virtual int score(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::sub && (((binOpNode*)input)->getR()->type() == nodeTypes::integral ||
		((binOpNode*)input)->getR()->type() == nodeTypes::integral))
		{
			return 0;
		}
		return 1;
	}

	virtual ~unchainMetric() {}
};


#endif
