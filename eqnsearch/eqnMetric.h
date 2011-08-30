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
#ifndef NN_EQNMETRIC_H
#define NN_EQNMETRIC_H

#include "../parse/nodes/eqnNode.h"
#include "../parse/nodes/nodeTypes.h"
#include "../parse/nodes/binOpNode.h"
#include "../parse/nodes/monoOpNode.h"
#include <cmath>

/**
 * @class eqnMetric
 *
 * @brief Base class for all eqnNode* metrics.
 *
 * @details not pure virutal, but only returns the metrics size.
 */


class eqnMetric
{
	public:
	/**
	 * @brief the number of derivNode*'s in the parse tree
	 * @param input the eqnNode* to be analyzed
	 * @returns number of derivatives
	 */
	int countd(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::deriv)
		{
			return countd(((binOpNode*)input)->getL())*
				countd(((binOpNode*)input)->getL()) + 1;
		}
		else if (input->isBin())
		{
			return countd(((binOpNode*)input)->getL()) 
				+ countd(((binOpNode*)input)->getR());
		}
		else if (input->isMono())
		{
			return countd(((monoOpNode*)input)->getR()); 
		}
		
		return 0;
		
	}

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

	/**
	 * @brief standard integer square-root
	 * @param input argument of the quare root
	 * @returns the quare root of input
	 */
	static int isqrt(int input)
	{
		double a,b;
		b = 1;
		do
		{
			a = b;
			b = (a + ((double)input)/a )/2.0;
		} while (fabs(b-a) > 0.75);

		return (int)floor(b);
	}


	/**
	 * @brief a mapping from expressions to integers
	 *
	 * @details Depending on the intended use of the metric, eqnNode*'s
	 * are traversed and a integer value is calculated. In the basic
	 * case this is simply the number of nodes in the tree
	 *
	 * @param input the supplied eqnNode*, to be analyzed
	 *
	 * @returns the calculated integer value
	 */
	virtual int score(const eqnNode* input) const
	{
		return input->size();
	}

	virtual ~eqnMetric() { }
};


#endif
