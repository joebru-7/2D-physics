#pragma once
#include "Point.h"
#include "sdl_wrappers.h"

class Asteroid
{
public:
	FPoint pos = { 100,100 };
	FPoint velocity{ 0,0 }; //px/s
	float rotationAngle{ 0 };//rad
	float AngularVelocity{0};//rad/s
	const FPoint graphics[8] = { {-8,-10},{-10,8},{-7,10},{10,10},{10,6},{2,6},{-4,-2},{-8,-10} };
	FPoint worldpoints[8] = {};
	
public:
	Asteroid() = default;
	Asteroid(FPoint pos, FPoint velocity, float rotationAngle, float AngularVelocity)
		:pos(pos), velocity(velocity), rotationAngle(rotationAngle), AngularVelocity(AngularVelocity)
	{};

	int Draw(Renderer& rend);
	void Update(float deltatime);
};

