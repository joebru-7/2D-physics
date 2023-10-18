#pragma once
#include "sdl_wrappers.h"

class Drawable
{
protected:
	FPoint pos = { 100,100 };
	float rotationAngle{ 0 };//rad
	int count = 8;
	//const FPoint* const graphics = nullptr;
	int OfsetOfworldpoints;

public:
	Drawable() = default;
	Drawable(FPoint pos, float rotationAngle, int count, int OfsetOfworldpoints)
		:pos(pos),rotationAngle(rotationAngle),count(count), OfsetOfworldpoints(OfsetOfworldpoints)
	{}
	
	virtual ~Drawable() = default;

	virtual int Draw(Renderer& rend)
	{
		return rend.DrawLines(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count);
	}
	
};