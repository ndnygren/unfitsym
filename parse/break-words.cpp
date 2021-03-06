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

#include "break-words.h"

using namespace std;

bool breakWords::n_alpha(char t)
{
	switch(t)
	{
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f': case 'g': case 'h': case 'i': case 'j':
			case 'k': case 'l': case 'm': case 'n': case 'o':
			case 'p': case 'q': case 'r': case 's': case 't':
			case 'u': case 'v': case 'w': case 'x': case 'y':
			case 'z': 
				return false;
	}	
	return true;
}

bool breakWords::n_num(char t)
{
	switch(t)
	{
		case '0':	return false;
		case '1':	return false;
		case '2':	return false;
		case '3':	return false;
		case '4':	return false;
		case '5':	return false;
		case '6':	return false;
		case '7':	return false;
		case '8':	return false;
		case '9':	return false;
		case '.':	return false;
	}	
	return true;
}

bool breakWords::n_oper(char t)
{
	switch(t)
	{
		case '+':	return false;
		case '-':	return false;
		case '*':	return false;
		case '/':	return false;
	}	
	return true;
}

bool breakWords::nlrsqb(char t)
{
	switch(t)
	{
		case '[':	return false;
		case ']':	return false;
	}	
	return true;
}

bool breakWords::lrsqb(char t)
{
	switch(t)
	{
		case '[':	return true;
		case ']':	return true;
	}	
	return false;
}

bool breakWords::w_only(char t)
{
	switch(t)
	{
		case ' ':	return true;
		case '\n':	return true;
		case '\r':	return true;
		case '\t':	return true;
	}	
	return false;
}

bool breakWords::w_commas(char t)
{
	switch(t)
	{
		case ',':	return true;
		case ' ':	return true;
		case '\n':	return true;
		case '\r':	return true;
		case '\t':	return true;
	}	
	return false;
}

string breakWords::stripwhite(const string& input, bool (*whitespc)(char))
{
	unsigned int i = 0;
	vector<string> v_words = breakwords(input, whitespc);
	string output = "";
	
	for(i = 0; i < v_words.size(); i++)
	{
		output = output + v_words[i];
	}
	return output;

}

vector<string> breakWords::breakwords(const string& input, bool (*whitespc)(char))
{
	int wordstart = -1;
	int count = 0;
	unsigned int i = 0;
	vector<string> v_words;

	for (i = 0; i < input.length(); i++)
	{
		if ((*whitespc)(input[i]))
		{
			if (wordstart != -1)
			{
					v_words.push_back(input.substr(
						wordstart, i - wordstart));
				wordstart = -1;
				count++;
			}
		}
		else if (wordstart == -1) { wordstart = i; }
		
	}
	if (wordstart != -1)
	{
			v_words.push_back(input.substr(wordstart, 
				input.length() - wordstart));
		wordstart = -1;
		count++;	
	}
	return v_words;
}

vector<string> breakWords::breakwords(const string& input, const string& breaker)
{
	int wordstart = -1;
	int count = 0;
	unsigned int i = 0;
	vector<string> v_words;

	for (i = 0; i < input.length(); i++)
	{
		if (input.substr(i,breaker.length()) == breaker)
		{
			if (wordstart != -1)
			{
					v_words.push_back(input.substr(
						wordstart, i - wordstart));
				i+= breaker.length() - 1;
				wordstart = -1;
				count++;
			}
		}
		else if (wordstart == -1) { wordstart = i; }
		
	}
	if (wordstart != -1)
	{
			v_words.push_back(input.substr(wordstart, 
				input.length() - wordstart));
		wordstart = -1;
		count++;	
	}
	return v_words;
}

string breakWords::removeBetween(const string& input, const string& left, const string& right)
{
	unsigned int i,j,lastend;
	string outstring;

	lastend = 0;
	for (i = 0; i < input.length(); i++)
	{
		if (input.substr(i,left.length()) == left)
		{
			outstring += input.substr(lastend, i - lastend);
			for (j = i + left.length(); j < input.length(); j++)
			{
				if (input.substr(j,right.length()) == right)
				{
					lastend = j + right.length();
					i = j + right.length() - 1;
					j = input.length();
				}
			}
		}
	}
	outstring += input.substr(lastend, i - lastend);
	return outstring;
}

/*
	cout << "test: \'123\\*this is a comment*\\456\',\'\\*\',\'\\*\'" << endl;
	cout << removeBetween("123\\*this is a comment*\\456","\\*","*\\") << endl;
	cout << "test: \'\\*this is a comment*\\456\',\'\\*\',\'\\*\'" << endl;
	cout << removeBetween("\\*this is a comment*\\456","\\*","*\\") << endl;
	cout << "test: \'123\\*this is a comment*\\\',\'\\*\',\'\\*\'" << endl;
	cout << removeBetween("123\\*this is a comment*\\","\\*","*\\") << endl;*/
