#pragma once
#include "Point.h"
#include "sdl_wrappers.h"

class Asteroid
{
	FPoint pos = { 100,100 };
	FPoint velocity{ 0,0 };
	float rotationAngle{ 0 };
	FPoint graphics[8] = { {-8,-10},{-10,8},{-7,10},{10,10},{10,6},{2,6},{-4,-2},{-8,-10} };
	
public:
	Asteroid() = default;
	Asteroid(FPoint pos, FPoint velocity, float rotationAngle) 
		:pos(pos), velocity(velocity), rotationAngle(rotationAngle)
	{};

	int Draw(Renderer& rend);
	void Update(float deltatime);
};

