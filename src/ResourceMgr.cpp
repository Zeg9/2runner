/*
 2runner
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

#include <string>
#include <stdexcept>
#include "Video.h"
#include "Font.h"
//#include "Sound.h"
//#include "Tileset.h"
#include "ResourceMgr.h"
#include "tools.h"

#define DATA_PATH "../data/"

#define TRY_PATH(P) if (exists(P)) { return P; }
#define TRY_WRITE(P) if (canwrite(P)) { return P; }

#define GET_RESOURCE(FUNCTION, MAP, TYPE, PRE, SUF)\
	TYPE* ResourceMgr::FUNCTION(std::string name)\
	{\
		std::map<std::string,TYPE*>::iterator i = MAP.find(name);\
		if (i == MAP.end())\
		{\
			std::vector<std::string> toks = split(name,'&',2);\
			if (toks.size()==1)\
				MAP[name] = new TYPE(getPath(PRE+name+SUF));\
			else if (toks.size()==2)\
				MAP[name] = new TYPE(getPath(PRE+toks[0]+SUF)+'&'+toks[1]);\
			else\
				throw std::runtime_error("Error parsing resource name: "+name);\
			return MAP[name];\
		}\
		return i->second;\
	}

#define DEL_RESOURCE(MAP,TYPE)\
	for (std::map<std::string,TYPE*>::iterator i = MAP.begin(); i != MAP.end(); i++)\
		delete i->second;\
	MAP.clear();

#include <iostream>

ResourceMgr::ResourceMgr() {}

ResourceMgr::~ResourceMgr()
{
	unloadAll();
}

std::string ResourceMgr::getPath(std::string needle)
{
	#ifdef __unix__
	if (getenv("HOME"))
		TRY_PATH(std::string(getenv("HOME"))+"/.2runner/"+needle)
	#endif
	#ifdef WIN32
	if (getenv("APPDATA"))
		TRY_PATH(std::string(getenv("APPDATA"))+"/2runner/"+needle)
	#endif
	TRY_PATH("./"+needle)
	TRY_PATH("./data/"+needle)
	TRY_PATH("../data/"+needle)
	#ifdef __unix__
	TRY_PATH("/usr/share/2runner/"+needle)
	TRY_PATH("/usr/local/share/2runner/"+needle)
	#endif
	throw std::runtime_error("Couldn't find resource: "+needle);
}
std::string ResourceMgr::getWritePath(std::string needle)
{
	#ifdef __unix__
	if (getenv("HOME"))
		TRY_WRITE(std::string(getenv("HOME"))+"/.2runner/"+needle)
	#endif
	#ifdef WIN32
	if (getenv("APPDATA"))
		TRY_WRITE(std::string(getenv("APPDATA"))+"/2runner/"+needle)
	#endif
	TRY_WRITE(getPath(needle));
	TRY_WRITE("./"+needle)
	TRY_WRITE("./data/"+needle)
	TRY_WRITE("../data/"+needle)
	throw std::runtime_error("Couldn't write: "+needle);
}


GET_RESOURCE(getImage,images,Image,"",".png")
GET_RESOURCE(getFont,fonts,Font,"",".otf")
//GET_RESOURCE(getSound,sounds,Sound,"",".ogg")
//GET_RESOURCE(getTileset,tilesets,Tileset,"tilesets/","/tileset")

void ResourceMgr::unloadAll()
{
	//DEL_RESOURCE(tilesets,Tileset)
	DEL_RESOURCE(fonts,Font)
	DEL_RESOURCE(images,Image)
	//DEL_RESOURCE(sounds,Sound)
}

ResourceMgr &getResourceMgr()
{
	static ResourceMgr resourceMgr;
	return resourceMgr;
}
