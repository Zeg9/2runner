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
#ifndef __MENU_H__
#define __MENU_H__

#include <vector>
#include <string>
#include <SDL/SDL.h>

class Menu;

struct MenuEntry {
	MenuEntry(std::string n, std::string t, std::string v="",
		bool e=false, char i=0, char a=0, unsigned int l=0);
	std::string name;
	std::string text;
	std::string value;
	bool editable;
	char vmin, vmax;
	unsigned int vlen;
	void updateText();
	void event(SDL_Event &e, Menu*menu);
};

class Menu {
	friend struct MenuEntry;
	public:
		Menu(std::string t="");
		void add(MenuEntry e);
		MenuEntry &get();
		MenuEntry &get(std::string name);
		int event(SDL_Event &e);
		void render();
		bool loop();
	private:
		std::vector<MenuEntry> entries;
		std::string title;
		int select;
};

#endif//__MENU_H__
