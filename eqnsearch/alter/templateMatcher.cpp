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

using namespace std;

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

void templateMatcher::init()
{
	//addition:
	//commute
	addRule("TV_{1}+TV_{2} \\Rightarrow TV_{2}+TV_{1}");
	//associate one way
	addRule("(TV_{1}+TV_{2})+TV_{3} \\Rightarrow TV_{1}+(TV_{2}+TV_{3})");
	//associate the other way
	addRule("TV_{1}+(TV_{2}+TV_{3}) \\Rightarrow (TV_{1}+TV_{2})+TV_{3}");
	//check left identity
	addRule("0+TV_{1} \\Rightarrow TV_{1}");
	//check right identity
	addRule("TV_{1}+0 \\Rightarrow TV_{1}");
	//reverse distribute
	addRule("(TV_{1}*TV_{2}) + (TV_{1}*TV_{3}) \\Rightarrow TV_{1}*(TV_{2}+TV_{3})");
	//commute with right subtraction
	addRule("TV_{1}+(TV_{2}-TV_{3}) \\Rightarrow TV_{2}+(TV_{1}-TV_{3})");
	//handle frac
	addRule("TV_{1}+\\frac{TV_{2}}{TV_{3}} \\Rightarrow \\frac{(TV_{1}*TV_{3})+TV_{2}}{TV_{3}}");
	//handle neg
	addRule("TV_{1}+-TV_{2} \\Rightarrow TV_{1}-TV_{2}");
	//check	for same base
	addRule("(TV_{1}*TV_{2})+TV_{2} \\Rightarrow (TV_{1}+1)*TV_{2}");
	// check double
	addRule("TV_{2}+TV_{2} \\Rightarrow 2*TV_{2}");

	//subtraction
	//reduce to 0
	addRule("TV_{1}-TV_{1} \\Rightarrow 0");
	//replace with addition
	addRule("TV_{1}-TV_{2} \\Rightarrow TV_{1} + -TV_{2}");
	//neg on right
	addRule("TV_{1}--TV_{2} \\Rightarrow TV_{1}+TV_{2}");
	//distribute left over addition
	addRule("TV_{1}-(TV_{2}+TV_{3}) \\Rightarrow (TV_{1}-TV_{2})-TV_{3}");
	//distribute over left addition
	addRule("(TV_{1}-TV_{2})+TV_{3} \\Rightarrow TV_{1} - (TV_{2} - TV_{3})");
	//check same base
	addRule("(TV_{1}*TV_{2}) - (TV_{3}*TV_{2}) \\Rightarrow (TV_{1}-TV_{3})*TV_{2}");

	//fraction
	//seperate
	addRule("\\frac{TV_{1}}{TV_{2}} \\Rightarrow TV_{1}*\\frac{1}{TV_{2}}");
	//flip denominator up
	addRule("\\frac{TV_{1}}{\\frac{TV_{2}}{TV_{3}}} \\Rightarrow TV_{1}*\\frac{TV_{3}}{TV_{2}}");
	//numerator fraction down
	addRule("\\frac{\\frac{TV_{1}}{TV_{2}}}{TV_{3}} \\Rightarrow \\frac{TV_{1}}{TV_{2}*TV_{3}}");
	//right identity
	addRule("\\frac{TV_{1}}{1} \\Rightarrow TV_{1}");
	addRule("TV_{1} \\Rightarrow \\frac{TV_{1}}{1}");
	//zero numerator
	addRule("\\frac{0}{TV_{1}} \\Rightarrow 0");
	//reduce to 1
	addRule("\\frac{TV_{1}}{TV_{1}} \\Rightarrow 1");
	// ^{-1} in numerator
	addRule("\\frac{TV_{1}^{-1}}{TV_{2}} \\Rightarrow \\frac{1}{TV_{1}*TV_{2}}");
	// handle same expo
	addRule("\\frac{TV_{1}^{TV_{3}}}{TV_{2}^{TV_{3}}} \\Rightarrow \\frac{TV_{1}}{TV_{2}}^{TV_{3}}");
	addRule(" \\frac{TV_{1}}{TV_{2}}^{TV_{3}} \\Rightarrow \\frac{TV_{1}^{TV_{3}}}{TV_{2}^{TV_{3}}} ");
	// denominator expo
	addRule("\\frac{TV_{1}}{TV_{2}^{TV_{3}}} \\Rightarrow TV_{1}*TV_{2}^{-TV_{3}}");
	// numerator extraction
	addRule("\\frac{TV_{1}*TV_{2}}{TV_{3}} \\Rightarrow TV_{1}*\\frac{TV_{2}}{TV_{3}}");

	//hat
	// handle right identity
	addRule("TV_{1}^{1} \\Rightarrow TV_{1}");
	// handle left zero
	addRule("0^{TV_{1}} \\Rightarrow 0");
	// handle right zero
	addRule("{TV_{1}}^{0} \\Rightarrow 1");
	// handle right addition
	addRule("TV_{1}^{TV_{2}+TV_{3}} \\Rightarrow TV_{1}^{TV_{2}} + TV_{1}^{TV_{3}}");
	// base multiplication
	addRule("(TV_{1}*TV_{2})^{TV_{3}} \\Rightarrow TV_{1}^{TV_{3}}*TV_{2}^{TV_{3}}");
	// Right multiplication
	addRule("TV_{1}^{TV_{2}*TV_{3}} \\Rightarrow (TV_{1}^{TV_{2}})^{TV_{3}}");
	// hat chain
	addRule("(TV_{1}^{TV_{2}})^{TV_{3}} \\Rightarrow TV_{1}^{TV_{2}*TV_{3}}");	
	//flip
	addRule("TV_{1}^{TV_{2}} \\Rightarrow \\frac{1}{TV_{1}^{-TV_{2}}}");

	//identity
	// commute
	addRule("TV_{1}=TV_{2} \\Rightarrow TV_{2}=TV_{1}");
	// cancellation (additive)
	addRule("TV_{1}+TV_{2} = TV_{3}+TV_{2} \\Rightarrow TV_{1}=TV_{3}");
	addRule("TV_{2}+TV_{1} = TV_{2}+TV_{3} \\Rightarrow TV_{1}=TV_{3}");
	// move term (additive)
	addRule("TV_{1}+TV_{2} = TV_{3} \\Rightarrow TV_{1}= TV_{3}-TV_{2}");
	// move factor (denominator)
	addRule("\\frac{TV_{1}}{TV_{2}}=TV_{3} \\Rightarrow TV_{1}=TV_{2}*TV_{3}");


	// cosine
	// add remove 2 pi
	addRule("\\cos(TV_{1}) \\Rightarrow \\cos(TV_{1}+(2*\\pi))");
	addRule("\\cos(TV_{1}) \\Rightarrow \\cos(TV_{1}-(2*\\pi))");
	//handle 0
	addRule("\\cos(0) \\Rightarrow 1");
	//handle pi
	addRule("\\cos(\\pi) \\Rightarrow -1");
	addRule("\\cos(\\frac{\\pi}{2}) \\Rightarrow 0");
	addRule("\\cos(\\frac{3*\\pi}{2}) \\Rightarrow 0");
	//handle neg
	addRule("\\cos(-TV_{1}) \\Rightarrow \\cos(TV_{1})");
	// sine
	// add remove 2 pi
	addRule("\\sin(TV_{1}) \\Rightarrow \\sin(TV_{1}+(2*\\pi))");
	addRule("\\sin(TV_{1}) \\Rightarrow \\sin(TV_{1}-(2*\\pi))");
	//handle 0
	addRule("\\sin(0) \\Rightarrow 0");
	//handle pi
	addRule("\\sin(\\pi) \\Rightarrow 0");
	addRule("\\sin(\\frac{\\pi}{2}) \\Rightarrow 1");
	addRule("\\sin(\\frac{3*\\pi}{2}) \\Rightarrow -1");
	//handle neg
	addRule("\\sin(-TV_{1}) \\Rightarrow -\\sin(TV_{1})");

	//neg	
	//handle multiplcation
	addRule("-(TV_{1}*TV_{2}) \\Rightarrow (-TV_{1})*TV_{2}");
	addRule("-(TV_{1}*TV_{2}) \\Rightarrow TV_{1}*(-TV_{2})");
	//cancellation
	addRule("--TV_{1} \\Rightarrow TV_{1}");
	addRule("TV_{1} \\Rightarrow --TV_{1}");
	//distribute
	addRule("-(TV_{1}+TV_{2}) \\Rightarrow (-TV_{1})+(-TV_{2})");
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

