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
#ifndef NN_ISOSIMPMETRIC_H
#define NN_ISOSIMPMETRIC_H

#include "eqnMetric.h"
#include "isolateMetric.h"
#include <string>

class isoSimpMetric : public eqnMetric
{
	protected:
	std::string target;
	eqnMetric *simpPart;
	isolateMetric *isoPart;

	public:
	virtual int score(const eqnNode* input) const
	{
		return simpPart->score(input) + isoPart->score(input);
	}

	isoSimpMetric(std::string intarget)
	{
		target = intarget; 
		isoPart = new isolateMetric(target);
		simpPart = new eqnMetric();
	}

	virtual ~isoSimpMetric()
	{
		delete isoPart;
		delete simpPart;
	}
};


#endif
