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

using namespace std;

void generateProof::breakDown(const vector<pair<string, string> > &pairs, map<string, vector<string> > &edges) 
{
	unsigned int i;

	for (i = 0; i < pairs.size(); i++)
	{
		// initialize a vector if this is the first discovery
		if (edges.count(pairs[i].first) == 0)
		{
			edges[pairs[i].first] = vector<string>();
		}
		// add the "to" expression to the list of the associated "from" expression
		edges[pairs[i].first].push_back(pairs[i].second);
	} 
}

vector<string> generateProof::genVector(map<string, vector<string> > &edges, const string &start, const string &target) 
{
	unsigned int i;
	bool foundit=false; // flag for early exit in the case that the target is found
	vector<string> path; // the return value
	vector<string> list;
	map<string,crumb> found; // the crumb lookup map, for path finding
	queue<string> nextstr; // queue for breadth first search
	string current = start;
	crumb cr1(current);
	
	//initialize both the queue and crumb map
	nextstr.push(start);
	found[current] = cr1;

	do 
	{
		current = nextstr.front();
		nextstr.pop();

		if (current == target) { foundit = true; }
		else if (edges.count(current) > 0)
		{
			//store the temporary list, to cutdown on search time
			list = edges[current];

			for (i = 0; i < list.size(); i++)
			{
				//store only the first(shortest) reverse path found
				if (found.count(list[i])==0)
				{
					found[list[i]] = crumb(current, list[i]);
					nextstr.push(list[i]);
				}
			}
		}
	} while (!nextstr.empty() && !foundit);

	// if the target exists in the original pair list, it should have a proof
	if (found.count(target) > 0)
	{
		// start at the target and work back
		cr1 = found[target];
		while (found.count(cr1.back) > 0)
		{
			// trace the crumbs backward, building a list
			path.push_back(cr1.eqn);
			cr1 = found[cr1.back];
		}
		path.push_back(cr1.eqn);
	}
	return path;
}

string generateProof::convertVector(const vector<string> &path)
{
	int i;
	string outstring;
	
	for (i = (int)path.size()-1; i >= 0; i--)
	{
		outstring += path[i] + "\n";
	}

	return outstring;
}

string generateProof::build(const vector<pair<string, string> > &pairs, const string &start, const string &target)
{
	map<string, vector<string> > edges;
	breakDown(pairs, edges);
	
	return convertVector(genVector(edges, start, target));	
}

string generateProof::nice_build(const vector<pair<string, string> > &pairs, const string &start, const string &target)
{
	int i;
	string outstring;
	map<string, vector<string> > edges;
	breakDown(pairs, edges);
	vector<string> lines = genVector(edges, start, target);	
	
	for (i = (int)lines.size()-1; i >= 0; i--)
	{
		outstring += parserFull::makenice(lines[i]) + "\n";
	}

	return outstring;
}
