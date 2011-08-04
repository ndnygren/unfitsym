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

class derivMetric : public eqnMetric
{
	public:
	int countd(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::sum
			|| input->type() == nodeTypes::sub
			|| input->type() == nodeTypes::prod
			|| input->type() == nodeTypes::frac
			|| input->type() == nodeTypes::hat
			|| input->type() == nodeTypes::integral)
		{
			return countd(((binOpNode*)input)->getL()) 
				+ countd(((binOpNode*)input)->getR());
		}
		else if (input->type() == nodeTypes::neg
			|| input->type() == nodeTypes::sin
			|| input->type() == nodeTypes::cos
			|| input->type() == nodeTypes::ln)
		{
			return countd(((monoOpNode*)input)->getR()); 
		}
		else if (input->type() == nodeTypes::deriv)
		{
			return countd(((binOpNode*)input)->getL())*
				countd(((binOpNode*)input)->getL()) + 1;
		}
		
		return 0;
		
	}

	virtual int score(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::sum
			|| input->type() == nodeTypes::sub
			|| input->type() == nodeTypes::prod
			|| input->type() == nodeTypes::frac
			|| input->type() == nodeTypes::hat)
		{
			return score(((binOpNode*)input)->getL()) 
				+score(((binOpNode*)input)->getR()) + 1;
		}
		else if (input->type() == nodeTypes::neg
			|| input->type() == nodeTypes::sin
			|| input->type() == nodeTypes::cos
			|| input->type() == nodeTypes::ln)
		{
			return score(((monoOpNode*)input)->getR()) + 1; 
		}
		else if (input->type() == nodeTypes::deriv
			|| input->type() == nodeTypes::integral)
		{
			return score(((binOpNode*)input)->getL())*
				score(((binOpNode*)input)->getL());
		}
		
		return 1;
	}

	virtual ~derivMetric() {}
};


#endif
