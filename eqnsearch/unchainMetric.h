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
	/**
	 * @brief increments in the case that the argument is already greater than one.
	 * @param input the value to be incremented
	 * @returns input+1 if input > 0, otherwise 0.
	 */
	int bump(int input) const
	{
		if (input > 0) { return input + 1; }
		else { return 0; }
	}

	virtual int score(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::num
			&& input->type() == nodeTypes::var)
		{ 
			return 1;
		}
		else if (input->type() == nodeTypes::sum
			|| input->type() == nodeTypes::sub
			|| input->type() == nodeTypes::prod
			|| input->type() == nodeTypes::frac
			|| input->type() == nodeTypes::hat
			|| input->type() == nodeTypes::integral)
		{
			return bump(score(((binOpNode*)input)->getL()) 
				+score(((binOpNode*)input)->getR()));
			
		}
		else if (input->type() == nodeTypes::neg
			|| input->type() == nodeTypes::sin
			|| input->type() == nodeTypes::cos
			|| input->type() == nodeTypes::ln)
		{
			return bump(score(((monoOpNode*)input)->getR())); 
		}
		else if (input->type() == nodeTypes::deriv)
		{
			if (((derivNode*)input)->getL()->type() == nodeTypes::integral)
				{ return -5; }
			else
				{ return score(((derivNode*)input)->getL()); }
		}
		
		return 1;
	}

	virtual ~unchainMetric() {}
};


#endif
