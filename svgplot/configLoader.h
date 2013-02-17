/* svgplot - framework for symbolic computation
* Copyright (C) 2013 Nick Nygren
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


#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef NN_CONFIGLOADER_H
#define NN_CONFIGLOADER_H

class configLoader
{
	std::map<std::string, std::string> data;
	std::string blank;

	static std::string formatLine(const std::pair<std::string,std::string>& input)
	{
		std::string output;
		output = input.first;
		output += "=";
		output += input.second;
		return output;
	}

	public:
	void readline(const std::string& input)
	{
		int mid = first(input);

		if (mid == -1)
		{
//			std::cerr << "Error: \"" << input << '"' << " not formatted properly." << std::endl;
			return;
		}

		data[lowercase(stripwhite(input.substr(0,mid)))] = stripwhite(input.substr(mid + 1, (input.size() - mid) - 1));
	}

	std::string toString() const
	{
		std::map<std::string, std::string>::const_iterator it;
		std::string output;

		for (it = data.begin(); it != data.end(); it++)
		{
			output += formatLine(*it) + "\n";
		}

		return output;
	}

	static double toDouble(const std::string& input)
	{
		std::stringstream ss;
		double output;

		ss.str(input);

		ss >> output;

		return output;
	}

	static int toInt(const std::string& input)
	{
		std::stringstream ss;
		int output;

		ss.str(input);

		ss >> output;

		return output;
	}

	static bool white(char ch)
	{
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			{ return true; }
		else
			{ return false; }
	}

	static std::string stripwhite(const std::string input)
	{
		int i, first = -1, last = -1;

		for (i = 0; i < (int)input.size(); i++)
		{
			if (!white(input[i]) && first == -1)
				{ first = i; }
			if (!white(input[i]))
				{ last = i; }
		}

		if (first == -1) { return ""; }

		return input.substr(first, last - first + 1);
	}

	static std::string lowercase(const std::string input)
	{
		int i;
		std::string output = input;

		for (i = 0; i < (int)output.size(); i++)
		{
			if (output[i] >= 'A' && output[i] <= 'Z')
			{
				output[i] += 'a' - 'A';
			}
		}

		return output;
	}

	static int first(const std::string& input, char key)
	{
		int i;

		for (i = 0; i < (int)input.size(); i++)
		{
			if (input[i] == key)
			{
				return i;
			}
		}

		return -1;
	}

	void loadfile(const std::string& filename)
	{
		std::ifstream ifs;
		char buffer[5001];

		ifs.open(filename.c_str());

		if (!ifs.is_open())
		{
			std::cerr << "Error: could not open file: " << filename <<  std::endl;
			return;
		}

		while(!ifs.bad() && !ifs.eof())
		{
			ifs.getline(buffer, 5000);
			readline(buffer);
		}

		ifs.close();
	}

	static int first(const std::string& input)
	{
		return first(input, '=');
	}

	const std::string& operator[](const std::string& key) const
	{
		if (data.count(key) == 0) { return blank; }
		return data.find(key)->second;
	}

	configLoader()
	{
		blank = "";
	}
};

#endif


