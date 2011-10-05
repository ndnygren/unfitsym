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

#include "templateMatcher.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "../../parse/break-words.h"

using namespace std;

const char* templateMatcher::TM_RULEFILE = "rulelist";


vector<pair<eqnNode*,eqnNode*> > templateMatcher::rulelist;

void templateMatcher::varDefSort(std::vector<std::pair<int, eqnNode*> >& defs)
{
	// this is just insertion sort
	unsigned int i,j;
	pair<int, eqnNode*> temp;
	for (i = 1; i < defs.size(); i++)
	{
		j = i;
		while (j > 0)
		{
			if (defs[j].first < defs[j-1].first)
			{
				temp = defs[j];
				defs[j] = defs[j-1];
				defs[j-1] = temp;
			}
			j--;
		}
	}
}

void templateMatcher::varDefDup(std::vector<std::pair<int, eqnNode*> >& defs)
{
	unsigned int i;

	for (i = 0; i+1 < defs.size(); i++)
	{
		if (defs[i].first == defs[i+1].first)
		{
			delete defs[i+1].second;
			defs.erase(defs.begin()+i+1);
		}
	}
}

bool templateMatcher::varDefValidate(const std::vector<std::pair<int, eqnNode*> >& defs)
{
	unsigned int i;

	for (i = 0; i+1 < defs.size(); i++)
	{
		if (defs[i].first == defs[i+1].first
			&& !(defs[i].second->eq(defs[i+1].second)))
		{
			return false;
		}
	}
	return true;
}

void templateMatcher::varDefFree(std::vector<std::pair<int, eqnNode*> >& defs)
{
	while (defs.size() > 0)
	{
		delete defs.back().second;
		defs.pop_back();
	}
}

eqnNode* templateMatcher::fillPattern( const std::vector<std::pair<int, eqnNode*> >& defs, eqnNode* outpat)
{
	eqnNode *out = outpat->copy();
	unsigned int i;

	if (out->type() == nodeTypes::tvar)
	{
		for (i = 0; i < defs.size(); i++)
		{
			if (out->tNum() == defs[i].first)
			{
				delete out;
				return defs[i].second->copy();
			}
		}
	}
	else
	{
		for (i = 0; i < defs.size(); i++)
		{
			out->replace(defs[i].first,defs[i].second);
		}
	}

	return out;
}

void templateMatcher::createDefaultFile()
{
	ofstream ofile(TM_RULEFILE);
	
	if (ofile)
	{
		ofile << "//addition:\n";
		ofile << "//commute\n";
		ofile << "TV_{1}+TV_{2} \\Rightarrow TV_{2}+TV_{1}\\\\\n";
		ofile << "//associate one way\n";
		ofile << "(TV_{1}+TV_{2})+TV_{3} \\Rightarrow TV_{1}+(TV_{2}+TV_{3})\\\\\n";
		ofile << "//associate the other way\n";
		ofile << "TV_{1}+(TV_{2}+TV_{3}) \\Rightarrow (TV_{1}+TV_{2})+TV_{3}\\\\\n";
		ofile << "//check left identity\n";
		ofile << "0+TV_{1} \\Rightarrow TV_{1}\\\\\n";
		ofile << "//check right identity\n";
		ofile << "TV_{1}+0 \\Rightarrow TV_{1}\\\\\n";
		ofile << "//reverse distribute\n";
		ofile << "(TV_{1}*TV_{2}) + (TV_{1}*TV_{3}) \\Rightarrow TV_{1}*(TV_{2}+TV_{3})\\\\\n";
		ofile << "//commute with right subtraction\n";
		ofile << "TV_{1}+(TV_{2}-TV_{3}) \\Rightarrow TV_{2}+(TV_{1}-TV_{3})\\\\\n";
		ofile << "//handle frac\n";
		ofile << "TV_{1}+\\frac{TV_{2}}{TV_{3}} \\Rightarrow \\frac{(TV_{1}*TV_{3})+TV_{2}}{TV_{3}}\\\\\n";
		ofile << "//handle neg\n";
		ofile << "TV_{1}+-TV_{2} \\Rightarrow TV_{1}-TV_{2}\\\\\n";
		ofile << "//check for same base\n";
		ofile << "(TV_{1}*TV_{2})+TV_{2} \\Rightarrow (TV_{1}+1)*TV_{2}\\\\\n";
		ofile << "// check double\n";
		ofile << "TV_{2}+TV_{2} \\Rightarrow 2*TV_{2}\\\\\n";

		ofile << "//subtraction\n";
		ofile << "//reduce to 0\n";
		ofile << "TV_{1}-TV_{1} \\Rightarrow 0\\\\\n";
		ofile << "//replace with addition\n";
		ofile << "TV_{1}-TV_{2} \\Rightarrow TV_{1} + -TV_{2}\\\\\n";
		ofile << "//neg on right\n";
		ofile << "TV_{1}--TV_{2} \\Rightarrow TV_{1}+TV_{2}\\\\\n";
		ofile << "//distribute left over addition\n";
		ofile << "TV_{1}-(TV_{2}+TV_{3}) \\Rightarrow (TV_{1}-TV_{2})-TV_{3}\\\\\n";
		ofile << "//distribute over left addition\n";
		ofile << "(TV_{1}-TV_{2})+TV_{3} \\Rightarrow TV_{1} - (TV_{2} - TV_{3})\\\\\n";
		ofile << "//check same base\n";
		ofile << "(TV_{1}*TV_{2}) - (TV_{3}*TV_{2}) \\Rightarrow (TV_{1}-TV_{3})*TV_{2}\\\\\n";

		ofile << "//prod\n";
		ofile << "//commute\n";
		ofile << "TV_{1}*TV_{2} \\Rightarrow TV_{2}*TV_{1}\\\\\n";
		ofile << "//associate one way\n";
		ofile << "(TV_{1}*TV_{2})*TV_{3} \\Rightarrow TV_{1}*(TV_{2}*TV_{3})\\\\\n";
		ofile << "//associate the other way\n";
		ofile << "TV_{1}*(TV_{2}*TV_{3}) \\Rightarrow (TV_{1}*TV_{2})*TV_{3}\\\\\n";
		ofile << "//check left identity\n";
		ofile << "1*TV_{1} \\Rightarrow TV_{1}\\\\\n";
		ofile << "//check right identity\n";
		ofile << "TV_{1}*1 \\Rightarrow TV_{1}\\\\\n";
		ofile << "//check left zero\n";
		ofile << "0*TV_{1} \\Rightarrow 0\\\\\n";
		ofile << "//check right zero\n";
		ofile << "TV_{1}*0 \\Rightarrow 0\\\\\n";
		ofile << "//create neg\n";
		ofile << "-1*TV_{1} \\Rightarrow -TV_{1}\\\\\n";
		ofile << "// handle frac\n";
		ofile << "TV_{1}*\\frac{TV_{2}}{TV_{3}} \\Rightarrow \\frac{TV_{1}*TV_{2}}{TV_{3}}\\\\\n";
		ofile << "// distribute over addition\n";
		ofile << "TV_{1}*(TV_{2}+TV_{3}) \\Rightarrow (TV_{1}*TV_{2}) + (TV_{1}*TV_{3})\\\\\n";
		ofile << "// distribute over subtraction\n";
		ofile << "TV_{1}*(TV_{2}-TV_{3}) \\Rightarrow (TV_{1}*TV_{2}) - (TV_{1}*TV_{3})\\\\\n";
		ofile << "// exp same bases\n";
		ofile << "TV_{1}^{TV_{2}}*(TV_{1}^{TV_{3}}) \\Rightarrow TV_{1}^{TV_{2}+TV_{3}}\\\\\n";
		ofile << "TV_{1}^{TV_{2}}*TV_{1} \\Rightarrow TV_{1}^{TV_{2}+1}\\\\\n";
		ofile << "TV_{1}*(TV_{1}^{TV_{3}}) \\Rightarrow TV_{1}^{1+TV_{3}}\\\\\n";
		ofile << "TV_{1}*TV_{1} \\Rightarrow TV_{1}^{2}\\\\\n";
		ofile << "// same exp\n";
		ofile << "TV_{1}^{TV_{3}}*(TV_{2}^{TV_{3}}) \\Rightarrow (TV_{1}*TV_{2})^{TV_{3}}\\\\\n";
		ofile << "// pull out neg\n";
		ofile << "TV_{1}*-TV_{2} \\Rightarrow -(TV_{1}*TV_{2})\\\\\n";
		ofile << "(-TV_{1})*TV_{2} \\Rightarrow -(TV_{1}*TV_{2})\\\\\n";
		

		ofile << "//fraction\n";
		ofile << "//seperate\n";
		ofile << "\\frac{TV_{1}}{TV_{2}} \\Rightarrow TV_{1}*\\frac{1}{TV_{2}}\\\\\n";
		ofile << "//flip denominator up\n";
		ofile << "\\frac{TV_{1}}{\\frac{TV_{2}}{TV_{3}}} \\Rightarrow TV_{1}*\\frac{TV_{3}}{TV_{2}}\\\\\n";
		ofile << "//numerator fraction down\n";
		ofile << "\\frac{\\frac{TV_{1}}{TV_{2}}}{TV_{3}} \\Rightarrow \\frac{TV_{1}}{TV_{2}*TV_{3}}\\\\\n";
		ofile << "//right identity\n";
		ofile << "\\frac{TV_{1}}{1} \\Rightarrow TV_{1}\\\\\n";
		ofile << "TV_{1} \\Rightarrow \\frac{TV_{1}}{1}\\\\\n";
		ofile << "//zero numerator\n";
		ofile << "\\frac{0}{TV_{1}} \\Rightarrow 0\\\\\n";
		ofile << "//reduce to 1\n";
		ofile << "\\frac{TV_{1}}{TV_{1}} \\Rightarrow 1\\\\\n";
		ofile << "// ^{-1} in numerator\n";
		ofile << "\\frac{TV_{1}^{-1}}{TV_{2}} \\Rightarrow \\frac{1}{TV_{1}*TV_{2}}\\\\\n";
		ofile << "// handle same expo\n";
		ofile << "\\frac{TV_{1}^{TV_{3}}}{TV_{2}^{TV_{3}}} \\Rightarrow \\frac{TV_{1}}{TV_{2}}^{TV_{3}}\\\\\n";
		ofile << " \\frac{TV_{1}}{TV_{2}}^{TV_{3}} \\Rightarrow \\frac{TV_{1}^{TV_{3}}}{TV_{2}^{TV_{3}}} \\\\\n";
		ofile << "// denominator expo\n";
		ofile << "\\frac{TV_{1}}{TV_{2}^{TV_{3}}} \\Rightarrow TV_{1}*TV_{2}^{-TV_{3}}\\\\\n";
		ofile << "// numerator extraction\n";
		ofile << "\\frac{TV_{1}*TV_{2}}{TV_{3}} \\Rightarrow TV_{1}*\\frac{TV_{2}}{TV_{3}}\\\\\n";

		ofile << "//hat\n";
		ofile << "// handle right identity\n";
		ofile << "TV_{1}^{1} \\Rightarrow TV_{1}\\\\\n";
		ofile << "// handle left zero\n";
		ofile << "0^{TV_{1}} \\Rightarrow 0\\\\\n";
		ofile << "// handle right zero\n";
		ofile << "{TV_{1}}^{0} \\Rightarrow 1\\\\\n";
		ofile << "// handle right addition\n";
		ofile << "TV_{1}^{TV_{2}+TV_{3}} \\Rightarrow TV_{1}^{TV_{2}} + TV_{1}^{TV_{3}}\\\\\n";
		ofile << "// base multiplication\n";
		ofile << "(TV_{1}*TV_{2})^{TV_{3}} \\Rightarrow TV_{1}^{TV_{3}}*TV_{2}^{TV_{3}}\\\\\n";
		ofile << "// Right multiplication\n";
		ofile << "TV_{1}^{TV_{2}*TV_{3}} \\Rightarrow (TV_{1}^{TV_{2}})^{TV_{3}}\\\\\n";
		ofile << "// hat chain\n";
		ofile << "(TV_{1}^{TV_{2}})^{TV_{3}} \\Rightarrow TV_{1}^{TV_{2}*TV_{3}}\\\\\n";
		ofile << "//flip\n";
		ofile << "TV_{1}^{TV_{2}} \\Rightarrow \\frac{1}{TV_{1}^{-TV_{2}}}\\\\\n";

		ofile << "//identity\n";
		ofile << "// commute\n";
		ofile << "TV_{1}=TV_{2} \\Rightarrow TV_{2}=TV_{1}\\\\\n";
		ofile << "// cancellation (additive)\n";
		ofile << "TV_{1}+TV_{2} = TV_{3}+TV_{2} \\Rightarrow TV_{1}=TV_{3}\\\\\n";
		ofile << "TV_{2}+TV_{1} = TV_{2}+TV_{3} \\Rightarrow TV_{1}=TV_{3}\\\\\n";
		ofile << "// move term (additive)\n";
		ofile << "TV_{1}+TV_{2} = TV_{3} \\Rightarrow TV_{1}= TV_{3}-TV_{2}\\\\\n";
		ofile << "// move factor (denominator)\n";
		ofile << "\\frac{TV_{1}}{TV_{2}}=TV_{3} \\Rightarrow TV_{1}=TV_{2}*TV_{3}\\\\\n";


		ofile << "// cosine\n";
		ofile << "// add remove 2 pi\n";
		ofile << "\\cos(TV_{1}) \\Rightarrow \\cos(TV_{1}+(2*\\pi))\\\\\n";
		ofile << "\\cos(TV_{1}) \\Rightarrow \\cos(TV_{1}-(2*\\pi))\\\\\n";
		ofile << "//handle 0\n";
		ofile << "\\cos(0) \\Rightarrow 1\\\\\n";
		ofile << "//handle pi\n";
		ofile << "\\cos(\\pi) \\Rightarrow -1\\\\\n";
		ofile << "\\cos(\\frac{\\pi}{2}) \\Rightarrow 0\\\\\n";
		ofile << "\\cos(\\frac{3*\\pi}{2}) \\Rightarrow 0\\\\\n";
		ofile << "//handle neg\n";
		ofile << "\\cos(-TV_{1}) \\Rightarrow \\cos(TV_{1})\\\\\n";
		ofile << "// sine\n";
		ofile << "// add remove 2 pi\n";
		ofile << "\\sin(TV_{1}) \\Rightarrow \\sin(TV_{1}+(2*\\pi))\\\\\n";
		ofile << "\\sin(TV_{1}) \\Rightarrow \\sin(TV_{1}-(2*\\pi))\\\\\n";
		ofile << "//handle 0\n";
		ofile << "\\sin(0) \\Rightarrow 0\\\\\n";
		ofile << "//handle pi\n";
		ofile << "\\sin(\\pi) \\Rightarrow 0\\\\\n";
		ofile << "\\sin(\\frac{\\pi}{2}) \\Rightarrow 1\\\\\n";
		ofile << "\\sin(\\frac{3*\\pi}{2}) \\Rightarrow -1\\\\\n";
		ofile << "//handle neg\n";
		ofile << "\\sin(-TV_{1}) \\Rightarrow -\\sin(TV_{1})\\\\\n";

		ofile << "//neg\n";
		ofile << "//handle multiplcation\n";
		ofile << "-(TV_{1}*TV_{2}) \\Rightarrow (-TV_{1})*TV_{2}\\\\\n";
		ofile << "-(TV_{1}*TV_{2}) \\Rightarrow TV_{1}*(-TV_{2})\\\\\n";
		ofile << "//cancellation\n";
		ofile << "--TV_{1} \\Rightarrow TV_{1}\\\\\n";
		ofile << "TV_{1} \\Rightarrow --TV_{1}\\\\\n";
		ofile << "//distribute\n";
		ofile << "-(TV_{1}+TV_{2}) \\Rightarrow (-TV_{1})+(-TV_{2})\\\\\n";
		
		ofile.flush();
		ofile.close();
	}
}

void templateMatcher::init()
{
	string filestring;
	string instring;
	vector<string> words;
	char ch;
	unsigned int i;

	ifstream ifile(TM_RULEFILE);
	if (!ifile)
	{
		ifile.close();
		createDefaultFile();
		ifile.open(TM_RULEFILE);
	}
	if (!ifile) { assert(ifile); }

	while (!ifile.eof())
	{
		ifile.get(ch);
		filestring += ch;
	}
	
	instring = breakWords::removeBetween(filestring,"\\*","*\\");
	instring = breakWords::removeBetween(instring,"//","\n");
	instring = breakWords::stripwhite(instring, breakWords::w_only);
	words = breakWords::breakwords(instring, "\\\\");
	for (i = 0; i < words.size(); i++)
	{
		addRule(words[i]);
//		cout << i << ": " << words[i] << endl;
	}
}

void templateMatcher::end()
{
	unsigned int i;

	for (i = 0; i < rulelist.size(); i++)
	{
		delete rulelist[i].first;
		delete rulelist[i].second;
	}

	rulelist.clear();
}

void templateMatcher::addRule(const std::string& input)
{
	pair<eqnNode*,eqnNode*> inpair = parserFull::readRule(input);
	
	if (inpair.first == 0)
	{
		cerr << "failed parse on rule " << rulelist.size() << ": ";
		cerr << input << endl;
	}

	assert(inpair.first != 0);

	rulelist.push_back(inpair);
}

std::vector<eqnNode*> templateMatcher::getMatches(const eqnNode* input)
{
	unsigned int j;
	pair<bool,vector<pair<int, eqnNode*> > > patmatch;
	vector<pair<int, eqnNode*> > defs;
	vector<eqnNode*> retlist;

	for (j = 0; j < rulelist.size(); j++)
	{
		patmatch = input->compareTemplate(rulelist[j].first);

		if (patmatch.first)
		{
//			cout << "matched:\t" << rulelist[j].first->nice_str() << endl;
			defs = patmatch.second;

			varDefSort(defs);

			if (varDefValidate(defs))
			{
				varDefDup(defs);
/*				for (i = 0; i < defs.size(); i++)
				{
					cout << defs[i].first << ":\t";
					cout << defs[i].second->nice_str() << endl;
				} */
				retlist.push_back(fillPattern(defs, rulelist[j].second));
			}
			varDefFree(defs);
		}
	}
	
/*	for (i = 0; i < retlist.size(); i++)
	{
		cout << "ret " << i << ":\t";
		cout << retlist[i]->nice_str() << endl;
	}
	cout << endl;*/

	return retlist;
}

