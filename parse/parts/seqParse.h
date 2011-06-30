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
#ifndef NN_SEQPARSE_H
#define NN_SEQPARSE_H

class seqParse : public parsePart
{
	protected:
	parsePart* left;

	public:
	void loadString(int offset, const std::string& data, int cap)
	{
		int i,x;
		succ.clear();
		left->loadString(offset, data, cap);
		while (left->getTrees().size() > 0)
		{
			for (i = 0; i < left->getTrees().size(); i++)
			{
				succ.push_back(left->getTrees()[i]);
			}
			left->loadString(succ.back().first, data, cap);
		}
	}

	seqParse(parsePart* lin)
	{
		left = lin;
	}
};

#endif
