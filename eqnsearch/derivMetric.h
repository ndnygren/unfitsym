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
#ifndef NN_DERIVMETRIC_H
#define NN_DERIVMETRIC_H

#include "../parse/nodes/eqnNode.h"
#include "../parse/nodes/nodeTypes.h"
#include "eqnMetric.h"
#include <string>

/**
 * @class derivMetric
 *
 * @brief Metric to encourage breaking derivatives down into smaller parts 
 * before solving.
 */


class derivMetric : public eqnMetric
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

	virtual int score(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::deriv
			|| input->type() == nodeTypes::integral)
		{
			return (score(((binOpNode*)input)->getL())+2)*
				(score(((binOpNode*)input)->getL())+2) +2;
		}
		else if (input->isBin())
		{
			return score(((binOpNode*)input)->getL()) 
				+score(((binOpNode*)input)->getR()) + 1;
		}
		else if (input->isMono())
		{
			return score(((monoOpNode*)input)->getR()) + 1; 
		}
		
		return 1;
	}

	virtual ~derivMetric() {}
};


#endif
