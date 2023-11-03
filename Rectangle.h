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

	FRectangle() = default;
	FRectangle(float x, float y, float w, float h) : SDL_FRect{ x,y,w,h } {}
	FRectangle(const FPoint (&points)[2] )
	{
		SDL_EncloseFPoints(points, 2, nullptr, this);
	}

	bool operator==(const FRectangle& other) const
	{
		return SDL_FRectEquals(this, &other);
	}

	bool isIntersecting(const FRectangle& other) const
	{
		return SDL_HasIntersectionF(this, &other);
	}

	bool isContaining(const FRectangle& other) const
	{
		FRectangle test{};
		SDL_IntersectFRect(this, &other, &test);
		return other == test;
	}


};

inline Rectangle::operator FRectangle()
{
	return { (float)x,(float)y,(float)w,(float)h, };

}