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

#ifndef __FONT_H__
#define __FONT_H__

#include <string>
#include <SDL/SDL_ttf.h>

enum Align {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};
enum VAlign {
	ALIGN_TOP,
	ALIGN_MIDDLE,
	ALIGN_BOTTOM
};

class Font
{
	public:
		Font(std::string def);
		~Font();
		void render(std::string text,
			Uint8 r=0, Uint8 g=0, Uint8 b=0,
			int x=0, int y=0, Align a=ALIGN_LEFT, VAlign v=ALIGN_TOP);
	private:
		TTF_Font *font;
};

#endif//__FONT_H__
