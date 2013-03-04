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

#include <stdexcept>
#include "Video.h"
#include "Font.h"
#include "ResourceMgr.h"
#include "Menu.h"

MenuEntry::MenuEntry(
	std::string n, std::string t, std::string v,
	bool e, char i, char a, unsigned int l)
 : name(n), text(t), value(v),
   editable(e), vmin(i), vmax(a), vlen(l) {}

void MenuEntry::updateText()
{
	if (!editable) return;
	std::string n(name);
	n[0] = toupper(n[0]);
	text = n + ": " + value;
}

void MenuEntry::event(SDL_Event &e, Menu*menu)
{
	if (!editable) return;
	updateText();
	if (&(menu->get()) != this) return;
	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_BACKSPACE:
					value = value.substr(0,value.size()-1);
					break;
				default:
					break;
			}
			{
				char u = e.key.keysym.unicode;
				if (vlen > 0 && value.size() >= vlen) break;
				if (u < vmin || u > vmax) break;
				value += u;
			}
			break;
	}
	updateText();
	text = text + '_';
}

Menu::Menu(std::string t) : title(t), select(0)
{}

void Menu::add(MenuEntry e)
{
	entries.push_back(e);
}
MenuEntry &Menu::get()
{
	return entries[select];
}
MenuEntry &Menu::get(std::string name)
{
	for (unsigned int i = 0; i < entries.size(); i++)
	{
		if (entries[i].name == name)
			return entries[i];
	}
	throw std::runtime_error("Couldn't find menu entry with name: "+name);
}

int Menu::event(SDL_Event &e)
{
	Device &d = getDevice();
	int menux = d.getWidth()/2;
	int menuy = d.getHeight()/2 - (40*entries.size())/2;
	int r = -2;
	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					r = select;
					break;
				case SDLK_DOWN:
					if (select < (int)entries.size()-1)
						select++;
					else select = 0;
					break;
				case SDLK_UP:
					if (select > 0)
						select--;
					else select = entries.size()-1;
					break;
				default:
					break;
			}
			break;
		case SDL_MOUSEMOTION:
			if (e.motion.y > menuy && e.motion.y < menuy+entries.size()*40
			 && e.motion.x > menux-128 && e.motion.x < menux+128)
			{
				int n = (e.motion.y-menuy)/40;
				if (n >= 0 && n < (int)entries.size())
					select = n;
			} else select = -1;
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)
				r = select;
			break;
		default:
			break;
	}
	for (unsigned int i = 0; i < entries.size(); i++)
		entries[i].event(e, this);
	return r;
}

void Menu::render()
{
	Device &d = getDevice();
	int menux = d.getWidth()/2;
	int menuy = d.getHeight()/2 - (40*entries.size())/2;
	for (unsigned int i = 0; i < entries.size(); i++)
	{
		uint8_t grey = 128;
		if (select == (int)i)
			grey = 255;
		getResourceMgr().getFont("common/FreeSans&16")->render(
			entries[i].text, grey,grey,grey,
			menux, menuy+i*40+16,
			ALIGN_CENTER, ALIGN_MIDDLE);
	}
}

bool Menu::loop()
{
	Device &d = getDevice();
	Image *scr = d.screenshot();
	scr->setAlpha(64);
	SDL_Event e;
	bool accept=false;
	bool done=false;
	while (d.run() && !done)
	{
		d.clear();
		d.drawImage(scr);
		getResourceMgr().getFont("common/FreeSans&48")->render
			(title,255,255,255,48,48);
		render();
		d.render();
		while (d.hasEvent())
		{
			e = d.nextEvent();
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				done = true;
			if (event(e) >= 0)
			{
				MenuEntry &entry = get();
				if (entry.name == "cancel")
					done = true;
				if (entry.name == "accept")
				{
					accept = true;
					done = true;
				}
			}
		}
	}
	delete scr;
	return accept;
}

