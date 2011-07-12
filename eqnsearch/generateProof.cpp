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

#include "generateProof.h"
#include <iostream>

using namespace std;

void generateProof::breakDown(const vector<pair<string, string> > &pairs, map<string, vector<string> > &edges) 
{
	unsigned int i;

	for (i = 0; i < pairs.size(); i++)
	{
		if (edges.count(pairs[i].first) == 0)
		{
			edges[pairs[i].first] = vector<string>();
			edges[pairs[i].first];
		}
		edges[pairs[i].first].push_back(pairs[i].second);
	} 
}

vector<string> generateProof::genVector(map<string, vector<string> > &edges, const string &start, const string &target) 
{
	unsigned int i;
	bool foundit=false;
	vector<string> path;
	vector<string> list;
	map<string,crumb> found;
	queue<string> nextstr;
	string current = start;
	crumb cr1(current);
	
	nextstr.push(start);
	found[current] = cr1;

	do 
	{
		current = nextstr.front();
		nextstr.pop();

		if (current == target) { foundit = true; }
		else if (edges.count(current) > 0)
		{
			cr1 = found[current]; 
			list = edges[current];

			for (i = 0; i < list.size(); i++)
			{
				if (found.count(list[i])==0)
				{
					found[list[i]] = crumb(current, list[i]);
					nextstr.push(list[i]);
				}
			}
		}
	} while (!nextstr.empty() && !foundit);

	if (found.count(target) > 0)
	{
		cr1 = found[target];
		while (cr1.back != "")
		{
			cout << "pushing: " << cr1.eqn << endl;
			path.push_back(cr1.eqn);
			cr1 = found[cr1.back];
		}
		path.push_back(cr1.eqn);
	}
	return path;
}

std::string generateProof::convertVector(const std::vector<std::string> &path)
{
	unsigned int i;
	std::string outstring;
	
	for (i = path.size()-1; i >= 0; i--)
	{
//			outstring += path[i] + "\n";
	}

	return outstring;
}

std::string generateProof::build(const std::vector<pair<std::string, std::string> > &pairs, const std::string &start, const std::string &target)
{
	std::map<std::string, std::vector<std::string> > edges;
	breakDown(pairs, edges);
	
	return convertVector(genVector(edges, start, target));	
}
