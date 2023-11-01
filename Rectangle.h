#pragma once
#include "sdl_wrappers.h"
#include "Point.h"

struct FRectangle;
struct Rectangle : SDL_Rect
{
	explicit operator FRectangle();
};

struct FRectangle : SDL_FRect
{
	explicit operator Rectangle()
	{
		return { (int)x,(int)y,(int)w,(int)h, };
	}

	bool isIntersecting(const FRectangle& other)
	{
		return SDL_HasIntersectionF(this, &other);
	}
};

inline Rectangle::operator FRectangle()
{
	return { (float)x,(float)y,(float)w,(float)h, };

}