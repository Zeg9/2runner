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

#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <stack>
#include <string>
#include <SDL/SDL.h>
#include "types.h"

// You can change the resolution here
// It is recommended to keep a relatively small one,
// because the game become really laggy with higher ones.
// You should keep multiples of 32 for both width and height.
// Default: 640x480
#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480

// Bits per pixel
// Minimum: 8
// Default: 32
#define VIDEO_BPP 32

// Optional SDL_FLAGS
#define VIDEO_SDL_FLAGS 0

// You can change the FPS here, but you shouldn't
// If you set higher FPS all the game will be faster,
// sprites (character, badguys, ...) too
#define MAX_FPS 60

// You shouldn't modify this.
#define TBF (1000/MAX_FPS+1) // Time between frames


class Image
{
	friend class Device;
	public:
		Image(std::string filename);
		Image(SDL_Surface *_surf);
		Image(const char **xpm);
		~Image();
		int getWidth();
		int getHeight();
		vec2 getSize();
		void setAlpha(Uint8 a);
	private:
		SDL_Surface *surf;
};

class Device
{
	friend Device &getDevice();
	public:
		int getWidth();
		int getHeight();
		void toggleFullscreen();
		void showCursor(bool show);
		// draw image by position
		void drawImage(Image *i, int x=0, int y=0);
		void drawImage(Image *i, vec2 p);
		// draw image by position and a clipping rect
		void drawImage(Image *i, int x, int y, int cx, int cy, int cw, int ch);
		// call this when the scene is drawn
		void render();
		void clear(Uint8 r=0, Uint8 g=0, Uint8 b=0);
		bool run();
		bool hasEvent();
		SDL_Event nextEvent();
		int getDTime();
		Image *screenshot();
		void quit(); // done = true
		void close(); // This closes the window faster
	private:
		Device();
		~Device();
		SDL_Surface *screen;
		std::stack<SDL_Event> eventStack;
		int lastticks; // last frame SDL_GetTicks()
		int cfps, lfps; // current, last fps
		bool fullscreen;
		bool cursor;
		bool done; // When set to true, the application exits
};
Device &getDevice();

#endif//__VIDEO_H__
