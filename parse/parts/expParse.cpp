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
#include "expParse.h"
#include <vector>
#include <cassert>

using namespace std;

void expParse::loadString(int offset, const std::string& data, int cap)
{
	assert(fails != 0);
	int i;
	natParse number;
	sumParse sums;
	subParse diff;
	prodParse prod;
	parenParse paren;
	curlyParse curly;
	varParse var;
	fracParse frac;
	negParse neg;
	hatParse hat;
	derivParse deriv;
	intParse integral;
	lnParse ln;
	sineParse sine;
	cosineParse cosine;
	idxParse indexed;
	tvarParse tvar;

	std::vector<parsePart*> exprs;
	
	exprs.push_back(&number);
	exprs.push_back(&sums);
	exprs.push_back(&diff);
	exprs.push_back(&prod);
	exprs.push_back(&paren);
	exprs.push_back(&curly);
	exprs.push_back(&var);
	exprs.push_back(&frac);
	exprs.push_back(&neg);
	exprs.push_back(&hat);
	exprs.push_back(&deriv);
	exprs.push_back(&integral);
	exprs.push_back(&ln);
	exprs.push_back(&sine);
	exprs.push_back(&cosine);
	exprs.push_back(&indexed);
	exprs.push_back(&tvar);

	deleteAll();
	
	if ((offset < (int)data.size() - cap) 
		&& ((*fails).count(pair<int,int>(offset,cap)) == 0))
	{
		for (i = 0; i < (int)exprs.size(); i++)
		{
			exprs[i]->setMap(fails);
			exprs[i]->loadString(offset, data, cap);
			copySucc(exprs[i]->getTrees()); 
		}
	
		(*fails)[pair<int,int>(offset,cap)] = copyList(succ);
	}
	else
	{
		succ = copyList((*fails)[pair<int,int>(offset,cap)]);
	}

}

expParse::expParse()
{
}
