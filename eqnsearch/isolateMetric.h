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
#include <string>

class isolateMetric : public eqnMetric
{
	protected:
	std::string target;

	public:
	int bump(int input) const
	{
		if (input > 0) { return input + 1; }
		else { return 0; }
	}

	virtual int score(const eqnNode* input) const
	{
		if (input->type() == nodeTypes::num)
			{ return 0; }
		else if (input->type() == nodeTypes::var)
		{
			if (((varNode*)input)->get() == target )
				{ return 1; }
			else { return 0; }
		}
		else if (input->type() == nodeTypes::sum
			|| input->type() == nodeTypes::sub
			|| input->type() == nodeTypes::prod
			|| input->type() == nodeTypes::frac
			|| input->type() == nodeTypes::hat)
		{
			return bump(score(((binOpNode*)input)->getL()) 
				+score(((binOpNode*)input)->getR()));
			
		}
		else if (input->type() == nodeTypes::neg)
		{
			return bump(score(((negNode*)input)->getR())); 
		}
		
		return (input->str()).length();
	}

	isolateMetric(std::string intarget)
		{ target = intarget; }

	virtual ~isolateMetric() {}
};


#endif
