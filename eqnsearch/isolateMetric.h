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
#ifndef NN_ISOLATEMETRIC_H
#define NN_ISOLATEMETRIC_H

#include "../parse/nodes/eqnNode.h"
#include "../parse/nodes/nodeTypes.h"
#include "eqnMetric.h"
#include <string>

/**
 * @class isolateMetric
 *
 * @brief Metric to lower the number of instances of a supplied variable and attempt to 'isolate' it from the rest of the expression
 */

class isolateMetric : public eqnMetric
{
	protected:
	/**
	 * @brief the variable to be isolated
	 */
	std::string target;

	public:

	virtual int score(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::var)
		{
			if (((varNode*)input)->get() == target )
				{ return 1; }
			else { return 0; }
		}
		else if (input->type() == nodeTypes::num)
		{
			if (((numNode*)input)->get() == 0) { return 1; }
			return isqrt(abs(((numNode*)input)->get()));
		}
		else if (input->type() == nodeTypes::idx)
		{
			return score(((binOpNode*)input)->getR()); 
		}
		else if (input->type() == nodeTypes::deriv
			|| input->type() == nodeTypes::integralb
			|| input->type() == nodeTypes::integral)
		{
			return (score(((binOpNode*)input)->getL()) + 2)*
				(score(((binOpNode*)input)->getL()) + 2)+2;
		}
		else if (input->isBin())
		{
			return bump(score(((binOpNode*)input)->getL()) 
				+score(((binOpNode*)input)->getR()));
			
		}
		else if (input->isMono())
		{
			return bump(score(((monoOpNode*)input)->getR())); 
		}
		
		return 0;
	}

	isolateMetric(std::string intarget)
		{ target = intarget; }

	virtual ~isolateMetric() {}
};


#endif
