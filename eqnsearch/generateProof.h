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
#ifndef NN_GENERATEPROOF_H
#define NN_GENERATEPROOF_H

#include <vector>
#include <queue>
#include <map>
#include <string>
#include <utility>
#include "../parse/parserFull.h"

/**
 * @class generateProof
 *
 * @brief Static functions, calculate proofs from adjacency matrices.
 *
 * @details The list of adjacent pairs is analyzed by the generateProof. It is convereted
 * 	into a forward look-up map. Then through a breadth first search, 
 *	a path(proof) is found from the first expression to the proof goal.
 *
 */
class generateProof
{
	protected:
	/**
	 * @class crumb
	 *
	 * @brief the trail of bread crumbs, allows backtracking in the 
	 * 	shortest possible path.
	 */
	class crumb
	{
		public:
		/**
		 * @brief the "previous" expression, in case of more than one,  
		 *	whichever was discovered first, gives the shortest path
		 */
		std::string back; 

		/**
		 * @brief the "current" expression
		 */
		std::string eqn;

		crumb(const std::string prev, const std::string &prevstr)
		{ back = prev; eqn = prevstr; }

		crumb(const std::string &prevstr)
		{ back = ""; eqn = prevstr; }

		crumb(const crumb &old)
		{ back = old.back; eqn = old.eqn; }

		crumb()
		{ back = ""; eqn = ""; }
	};

	 // void breakDown(const vector<pair<string, string> > &pairs, map<string, vector<string> > &edges)
	/**
	 * @brief Creates the forward look-up map from the list of pairs.
	 * @param pairs the input list of adjacent pairs
	 * @param edges the output forward lookup map
	 */
	static void breakDown(const std::vector<std::pair<std::string, std::string> > &pairs, std::map<std::string, std::vector<std::string> > &edges); 


	 // vector<string> genVector(map<string, vector<string> > &edges, const string &start, const string &target)
	/**
	 * @brief Generates the path in vector form from the forward look-up map.
	 * @param edges the graph represented as a forward look-up map
	 * @param start the node to begin searching from
	 * @param target the node to search for
	 * @returns a vector showing the shortest path from start to target through edges.
	 */
	static std::vector<std::string> genVector(std::map<std::string, std::vector<std::string> > &edges, const std::string &start, const std::string &target); 

	// string convertVector(const vector<string> &path)
	/**
	 * @brief Converts the vector formated proof into a single string.
	 * @param path the list of nodes
	 * @returns the single string path(proof)
	 */
	static std::string convertVector(const std::vector<std::string> &path);

	public:

	//string build(const vector< pair<string, string> > &pairs, const string &start, const string &target);
	/**
	 * @brief Using the list of pairs, a path(proof) from the start expression 
	 *	to the target expression is found.
	 * @param pairs the adjacency-list-represented graph
	 * @param start the initial expression
	 * @param target the chosen "solution" expression
	 *
	 * @returns the proof of the "solution" from the initial expression
	 */
	static std::string build(const std::vector<std::pair<std::string, std::string> > &pairs, const std::string &start, const std::string &target);

	/**
	 * @brief Same as generateProof::build(), except using the "nice" output
	 * @param pairs the adjacency-list-represented graph
	 * @param start the initial expression
	 * @param target the chosen "solution" expression
	 *
	 * @returns the proof of the "solution" from the initial expression
	 */
	static std::string nice_build(const std::vector<std::pair<std::string, std::string> > &pairs, const std::string &start, const std::string &target);
};

#endif
