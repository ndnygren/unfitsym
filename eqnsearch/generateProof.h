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

class generateProof
{
	protected:
	class crumb
	{
		public:
		std::string back;
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

	static void breakDown(const std::vector<std::pair<std::string, std::string> > &pairs, std::map<std::string, std::vector<std::string> > &edges); 

	static std::vector<std::string> genVector(std::map<std::string, std::vector<std::string> > &edges, const std::string &start, const std::string &target); 

	static std::string convertVector(const std::vector<std::string> &path);

	public:
	static std::string build(const std::vector<std::pair<std::string, std::string> > &pairs, const std::string &start, const std::string &target);
};

#endif
