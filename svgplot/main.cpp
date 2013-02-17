/* svgplot - framework for symbolic computation
* Copyright (C) 2013 Nick Nygren
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
#include <fstream>
#include "svgFactory.h"

char license[] = "svgplot  Copyright (C) 2013  Nick Nygren\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions.\n\n";

char created[] = "A sample.txt file has been created.\n\n";

char usage[] = "Usage:\n\tsvgplot <filename>\n\t\tCreates a svg file from the supplied config file\n\tsvgplot\n\t\tCreates a sample config file\n";

using namespace std;

string makeOutName(const string& input)
{
	if (input.length() < 4)
	{
		return input + ".svg";
	}
	else if (configLoader::lowercase(input).substr(input.length() - 4,4) == ".txt")
	{
		return input.substr(0,input.length() - 4) + ".svg";
	}
	else
	{
		return input + ".svg";
	}
}

int main(int argc, char ** argv)
{
	configLoader cfg;
	ofstream ofs;
	svgFactory fact(cfg);
	string outname;

	if (argc == 2)
	{
		cfg.loadfile(argv[1]);

		if (cfg["eqn1"] == "")
		{
			return -1;
		}

		fact.loadConfig(cfg);

		outname = makeOutName(argv[1]);

		ofs.open(outname.c_str());
		if (!ofs.is_open())
		{
			cerr << "Error: could not write to " << outname << endl;
			return -1;
		}

		ofs << fact.toString() << endl;

		ofs.close();
	}
	else if (argc == 1)
	{
		std::cerr << license;
		ofs.open("sample.txt");
		if (!ofs.is_open())
		{
			cerr << "Error: could not write to sample.txt." << endl;
			return -1;
		}
		else
		{
			cerr << created;
		}

		cerr << usage;

		ofs << "px_width = 1200" << endl;
		ofs << "px_height = 900" << endl;
		ofs << "eqn_x_min = -1" << endl;
		ofs << "eqn_y_min = -1" << endl;
		ofs << "eqn_x_max = 7" << endl;
		ofs << "eqn_y_max = 5" << endl;
		ofs << "border = 50" << endl;
		ofs << "step = .1" << endl;
		ofs << "eqn1 = \\frac{x^{2}}{2}" << endl;

		ofs.close();
	}
	else
	{
		cerr << "Error: Too many arguments." << endl;
		cerr << license << usage;
	}

	return 0;
}
