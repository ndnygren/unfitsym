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


/**
 * @brief Loads a specifies config file from the disk
 */
class configLoader
{
	/**
	 * @brief Main storage for the loaded data, maps variable names to given values
	 */
	std::map<std::string, std::string> data;

	/**
	 * @brief Pre-allocated blank string, to return blank as const reference
	 */
	std::string blank;

	/**
	 * @brief Converts a pair (for map iterator), to a formatted string, same format as can be read back by parser
	 * @param input The string/string pair returned by the map iterator
	 * @return The data from the pair, formatted in a string 
	 */
	static std::string formatLine(const std::pair<std::string,std::string>& input)
	{
		std::string output;
		output = input.first;
		output += "=";
		output += input.second;
		return output;
	}

	public:
	/**
	 * @brief Parser for a single line. Inserts the supplied definition into the map.
	 * @param input The formatted line from the config file.
	 */
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

	/**
	 * @brief Dumps the entire map to a string, which can be read back by another parser
	 * @return The string config data
	 */
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

	/**
	 * @brief Converts string to double
	 * @param input The string form number
	 * @return The numeric value
	 */
	static double toDouble(const std::string& input)
	{
		std::stringstream ss;
		double output;

		ss.str(input);

		ss >> output;

		return output;
	}

	/**
	 * @brief Converts string to int
	 * @param input The string form number
	 * @return The numeric value
	 */
	static int toInt(const std::string& input)
	{
		std::stringstream ss;
		int output;

		ss.str(input);

		ss >> output;

		return output;
	}

	/**
	 * @brief Tests a character for "whitespace"
	 * @param ch The character to test
	 * @return True if and only if ch is whitespace
	 */
	static bool white(char ch)
	{
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			{ return true; }
		else
			{ return false; }
	}

	/**
	 * @brief Strips leading and trailing whitespace from a string
	 * @param input The string to strip
	 * @return The string without leading/trailing whitespace
	 */
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

	/**
	 * @brief Converts a string to lowercase
	 * @param input The string to convert
	 * @return The lowercase string
	 */
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

	/**
	 * @brief Locates the first instance of 'key' in 'input'
	 * @param key The char to locate
	 * @param input The search area
	 * @return The location of 'key', or -1 if 'key' does not exist
	 */
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

	/**
	 * @brief Loads a given file into memory and parses it, storing the result in the map
	 * @param filename The filename
	 */
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

	/**
	 * @brief Overloaded function, same as above, with '=' as default key
	 */
	static int first(const std::string& input)
	{
		return first(input, '=');
	}

	/**
	 * @brief Const element access
	 * @param key The variable name to search for
	 * @return The value of the variable if it exists, otherwise blank
	 */
	const std::string& operator[](const std::string& key) const
	{
		if (data.count(key) == 0) { return blank; }
		return data.find(key)->second;
	}


	/**
	 * @brief Generates a list of all numbered entries in the config file beginning with a supplied prefix
	 * @param input The prefix of the numbered entries
	 * @return The list of stored values
	 */
	std::vector<std::string> startswith(const std::string& input) const
	{
		std::vector<std::string> output;
		std::map<std::string,std::string>::const_iterator it;
		unsigned int offs = input.length();

		for (it = data.begin(); it != data.end(); it++)
		{
			if (it->first.length() > offs)
			{
				if (it->first.substr(0, offs)==input && it->first[offs] >= '0' && it->first[offs] <= '9')
				{
					output.push_back(it->second);
				}
			}
		}

		return output;
	}

	configLoader()
	{
		blank = "";
	}
};

#endif


