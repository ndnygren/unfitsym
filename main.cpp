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
#include <iostream>
#include "parse/parserFull.h"
#include "eqnsearch/exprLinked.h"
#include "eqnsearch/searchMaxMin.cpp"
#include "eqnsearch/isoSimpMetric.h"

using namespace std;

int main(int argc, char** argv)
{
	unsigned int i;
	parserFull parser;
	eqnNode *output;
	eqnMetric *rate;
	searchMaxMin *a;
	vector<eqnNode*> list;

	rate = new isoSimpMetric("x");

	if (argc > 1)
	{
		cout << "input: " <<  argv[1] << "\n";
		output = parser.getExpr(argv[1]);
		if (output != 0)
		{
			cout << "parsed: " << output->str() << "\n";
			a = new searchMaxMin(output, rate);
			cout << "first 50:" << endl;
			list = a->best();

			for (i = 0; i < list.size(); i++)
				{ cout << list[i]->str() << endl; }

			a->next();
			cout << "second 50:" << endl;
			list = a->best();

			for (i = 0; i < list.size(); i++)
				{ cout << list[i]->str() << endl; }

			a->next();
			cout << "third 50:" << endl;
			list = a->best();

			for (i = 0; i < list.size(); i++)
				{ cout << list[i]->str() << endl; }
			

			a->next(500);
			cout << "500 more:" << endl;
			list = a->best();

			for (i = 0; i < list.size(); i++)
				{ cout << list[i]->str() << endl; }
			if (output != 0) { delete output; }

			delete a;
		}
	}

	delete rate;

	return 0;
}
