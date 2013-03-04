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

#include <vector>
#include <string>
#include "tools.h"
#include "Video.h"
#include "Font.h"


Font::Font(std::string def) : font(0)
{
	std::vector<std::string> toks = split(def,'&',2);
	std::string filename = toks[0];
	int size(16);
	if (toks.size()==2) size=toint(toks[1]);
	font = TTF_OpenFont(filename.c_str(),size);
}

Font::~Font()
{
	TTF_CloseFont(font);
}

void Font::render(std::string text,
	Uint8 r, Uint8 g, Uint8 b,
	int x, int y, Align a, VAlign v)
{
	SDL_Color color; color.r = r; color.g = g; color.b = b;
	int cx, cy;
	Image *t(0);
	std::vector<std::string> stext = split(text,"\n\r");
	std::string c("");
	for (unsigned int i = 0; i < stext.size(); i++)
	{
		c="";
		for (unsigned int j = 0; j < stext[i].size(); j++)
		{
			switch (stext[i][j])
			{
				case '\t':
					c += "    ";
					break;
				default:
					c += stext[i][j];
					break;
			}
		}
		t=new Image(TTF_RenderUTF8_Blended(font, c.c_str(), color));
		if (a==ALIGN_LEFT) cx = x;
		else if (a==ALIGN_CENTER) cx = x-t->getWidth()/2;
		else if (a==ALIGN_RIGHT) cx = x-t->getWidth();
		if (v==ALIGN_TOP) cy = y;
		else if (v==ALIGN_MIDDLE) cy = y-t->getHeight()*stext.size()/2;
		else if (v==ALIGN_BOTTOM) cy = y-t->getHeight()*stext.size();
		getDevice().drawImage(t,cx,cy+i*TTF_FontHeight(font));
		delete t;
	}
}

