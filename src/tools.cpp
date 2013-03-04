/*
 Platformutes
 Copyright (C) 2012-2013 Zeg9 <dazeg9@gmail.com>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <cmath>
#include "Video.h"
#include "tools.h"

#include <iostream>

std::string tostring(int i)
{
	std::ostringstream oss;
	oss << i;
	return oss.str();
}

int toint(std::string s)
{
	std::istringstream iss(s);
	int i;
	iss >> i;
	return i;
}

std::string tostring(bool b)
{
	if (b)
		return "true";
	return "false";
}

bool tobool(std::string s)
{
	if (toint(s)) return true;
	if (lowercase(s)=="true") return true;
	return false;
}

int round(int i, int f)
{
	if (i%f > f/2)
		return (i/f+1)*f;
	return (i/f)*f;
}

std::vector<std::string> split(std::string in, std::string seps, unsigned int max)
{
	std::vector<std::string> r;
	std::string current("");
	for (unsigned int i = 0; i < in.size(); i++)
	{
		if (seps.find(in[i]) != seps.npos && (max==0 || r.size()+1 < max))
		{
			if (current != "")
				r.push_back(current);
			current = "";
		}
		else
			current += in[i];
	}
	if (current != "")
		r.push_back(current);
	return r;
}
std::vector<std::string> split(std::string in, char sep, unsigned int max)
{
	std::string seps("");
	seps += sep;
	return split(in, seps, max);
}

std::string strip(std::string in, std::string what)
{
	std::string out("");
	for (unsigned int i = 0; i < in.size(); i++)
	{
		if (what.find(in[i]) == what.npos)
			out += in[i];
	}
	return out;
}

std::string stripspaces(std::string in)
{
	return strip(in, " \t\n\r");
}

std::string lowercase(std::string in)
{
	std::string out;
	for (unsigned int i = 0; i < in.size(); i++)
		out += tolower(in[i]);
	return out;
}

bool startswith(std::string s, std::string what)
{
	if (s.size() < what.size()) return false;
	if (s.substr(0,what.size()) == what) return true;
	return false;
}

bool exists(std::string fn)
{
	std::ifstream s (fn.c_str());
	return s;
}
bool canwrite(std::string fn)
{
	std::cout << "==== Trying to write: " << fn << std::endl;
	using namespace boost::filesystem;
	try {
		path p (fn);
		create_directories(p.parent_path());
		std::ofstream s (fn.c_str(),std::ios::ate);
		if (s.is_open())
			return true;
	} catch (...) {}
	std::cout << "====> Failed" << std::endl;
	return false;
}

int randint(int x, int y)
{
	int o = rand()%(y-x+1)+x;
	return o;
}

