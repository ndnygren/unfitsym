#include <iostream>
#include "configLoader.h"


using namespace std;

int main(int argc, char ** argv)
{
	cout << "\"" << configLoader::stripwhite("  a ") << "\"" << endl;
	cout << "\"" << configLoader::stripwhite(" df sia ") << "\"" << endl;
	cout << "\"" << configLoader::stripwhite("a ") << "\"" << endl;
	cout << "\"" << configLoader::stripwhite("  a") << "\"" << endl;
	cout << "\"" << configLoader::stripwhite("   ") << "\"" << endl;
	cout << configLoader::first("dsf=hfghf") << endl;
	return 0;
}
