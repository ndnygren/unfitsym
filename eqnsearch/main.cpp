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
#include "exprLinked.h"
#include "parserFull.h"
#include "searchMaxMin.cpp"

using namespace std;

int main(int argc, char** argv)
{
	parserFull parser;
	eqnNode *output;
	searchMaxMin *a;

	if (argc > 1)
	{
		cout << "input: " <<  argv[1] << "\n";
		output = parser.getExpr(argv[1]);
		if (output != 0)
		{
			cout << "parsed: " << output->str() << "\n";
			a = new searchMaxMin(output);
			if (output != 0) { delete output; }

			delete a;
		}
	}

	return 0;
}
