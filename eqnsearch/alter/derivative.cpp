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

#include "alterExpression.h"
#include "../derivMetric.h"
#include "../searchMaxMin.h"
#include <iostream>

using namespace std;

eqnNode* alterExpression::derivative(eqnNode* expression, std::string var)
{
	varNode vn(var);
	derivMetric rate;
	eqnNode* start = new derivNode(expression, &vn);
	eqnNode* bestcand = 0;
	searchMaxMin *engine = new searchMaxMin(start, &rate);
	
	while(bestcand == 0)
	{
		engine->next(100);
		bestcand = (engine->best(1))[0]->copy();

		if (rate.countd(bestcand) > 0)
		{
			delete bestcand;
			bestcand = 0;
		}
	}

	delete bestcand;
	engine->next(200);
	bestcand = (engine->best(1))[0]->copy();

	delete engine;
	delete start;

	return bestcand;
}
