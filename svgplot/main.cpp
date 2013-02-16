#include <iostream>
#include <fstream>
#include "configLoader.h"


using namespace std;

int main(int argc, char ** argv)
{
	configLoader cfg;
	ofstream ofs;

	if (argc > 1)
	{
		cfg.loadfile(argv[1]);
	}
	else
	{
		ofs.open("sample.txt");
		if (!ofs.is_open())
		{
			cerr << "Error: could not write to sample." << endl;
			return -1;
		}

		ofs << "x = 1" << endl;
		ofs << "y = 2" << endl;

		ofs.close();
	}

	cout << cfg.toString() << endl;

	return 0;
}
