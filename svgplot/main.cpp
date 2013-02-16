#include <iostream>
#include "configLoader.h"


using namespace std;

int main(int argc, char ** argv)
{
	configLoader cfg;

	cfg.readline("  One_data =	two ");
	cfg.readline(" Two_data	=\n banana ");
	cfg.readline(" Three_Data 	= gorilla\n");

	cout << cfg.toString() << endl;

	return 0;
}
