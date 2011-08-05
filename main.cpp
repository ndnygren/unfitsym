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
#include "eqnsearch/searchMaxMin.h"
#include "eqnsearch/isoSimpMetric.h"
#include "eqnsearch/generateProof.h"
#include "eqnsearch/alter/alterExpression.h"
#include "MainUFSearchWindow.h"

using namespace std;

int main(int argc, char** argv)
{
	unsigned int i;
	parserFull parser;
	eqnNode *output, *temp;
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
			temp = alterExpression::derivative(output,"x");
			cout << "derivative: " << temp->str() << "\n";
			delete temp;

			temp = alterExpression::collapse(output);
			cout << "collapse: " << temp->str() << "\n";
			delete temp;

			a = new searchMaxMin(output, rate);
			a->next(1000);
			cout << "best: ";
			list = a->best();

			for (i = 0; i < 1; i++)
				{ cout << list[i]->str() << endl; }
/*
			a->next();
			cout << "second 50:" << endl;
			list = a->best();

			for (i = 0; i < list.size(); i++)
				{ cout << list[i]->str() << endl; }

*/
			cout << "proof:" << endl;
			cout << generateProof::build(a->adjPairs, a->start->str(), list[0]->str()) << endl;
			

			if (output != 0) { delete output; }

			delete a;
		}
	}
	else
	{
		QApplication app(argc, argv);
		MainUFSearchWindow window;
		window.show();
		app.exec();
	}

	delete rate;

	return 0;
}
