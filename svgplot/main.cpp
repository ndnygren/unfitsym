#include <iostream>
#include <fstream>
#include "svgFactory.h"

using namespace std;

int main(int argc, char ** argv)
{
	configLoader cfg;
	ofstream ofs;
	svgFactory fact(cfg);

	if (argc > 1)
	{
		cfg.loadfile(argv[1]);
		fact.loadConfig(cfg);
		cout << fact.toString() << endl;
	}
	else
	{
		ofs.open("sample.txt");
		if (!ofs.is_open())
		{
			cerr << "Error: could not write to sample." << endl;
			return -1;
		}

		ofs << "px_width = 320" << endl;
		ofs << "px_height = 180" << endl;
		ofs << "eqn_x_min = -1" << endl;
		ofs << "eqn_y_min = -1" << endl;
		ofs << "eqn_x_max = 7" << endl;
		ofs << "eqn_y_max = 5" << endl;
		ofs << "border = 10" << endl;

		ofs.close();
	}

	return 0;
}
