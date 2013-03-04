#include "types.h"

vec2::vec2(int _x, int _y) :
	x(_x), y(_y)
	{}

bool operator==(vec2 const&a, vec2 const&b)
{
	return a.x == b.x && a.y == b.y;
}

