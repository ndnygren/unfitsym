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
#ifndef NN_NUMDOWNMETRIC_H
#define NN_NUMDOWNMETRIC_H

#include "../parse/nodes/eqnNode.h"
#include "eqnMetric.h"
#include <string>

/**
 * @class numDownMetric
 *
 * @brief Metric to encourage combining and reducigng numeric values. 
 */


class numDownMetric : public eqnMetric
{
	public:

	virtual int score(const eqnNode* input) const
	{
		if (input->isBin())
		{
			return score(((binOpNode*)input)->getL()) 
				+score(((binOpNode*)input)->getR());
		}
		else if (input->isMono())
		{
			return score(((monoOpNode*)input)->getR()); 
		}
		else if (input->type() == nodeTypes::num)
		{
			return abs(((numNode*)input)->get());
		}
		
		return 0;
	}

	virtual ~numDownMetric() {}
};


#endif
