
#include <map>
#include <vector>

#ifndef NN_CONFIGLOADER_H
#define NN_CONFIGLOADER_H

class configLoader
{
	std::map<std::string, std::string> data;

	public:
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

	static int first(const std::string& input)
	{
		return first(input, '=');
	}

	const std::string& operator[](const std::string& key) const
	{
		if (data.count(key) == 0) { return ""; }
		return data.find(key)->second;
	}
};

#endif


