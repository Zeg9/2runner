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

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include <vector>

std::string tostring(int i);
int toint(std::string s);
std::string tostring(bool b);
bool tobool(std::string s);

int round(int i, int f);

std::vector<std::string> split(std::string in,
	std::string seps, unsigned int max=0);
std::vector<std::string> split(std::string in,
	char sep, unsigned int max=0);
std::string strip(std::string in, std::string what);
std::string stripspaces(std::string in);
std::string lowercase(std::string in);

bool startswith(std::string s, std::string what);

bool exists(std::string fn);
bool canwrite(std::string fn); // warning: this creates the file

int randint(int x, int y);

#endif//__TOOLS_H__
