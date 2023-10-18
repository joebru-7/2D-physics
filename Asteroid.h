#pragma once
#include "Point.h"
#include "sdl_wrappers.h"

#include "Drawable.h"
#include <cstddef>

class Asteroid:public Drawable
{
public:
	//FPoint pos = { 100,100 };
	FPoint velocity{ 0,0 }; //px/s
	//float rotationAngle{ 0 };//rad
	float AngularVelocity{0};//rad/s
	FPoint worldpoints[8] = {};
	static const FPoint graphics[8];
public:
	Asteroid() = default;
	Asteroid(FPoint pos, FPoint velocity, float rotationAngle, float AngularVelocity)
		:Drawable(pos,rotationAngle,(int)std::size(worldpoints), offsetof(Asteroid,worldpoints)),
		//pos(pos), rotationAngle(rotationAngle),
		velocity(velocity), AngularVelocity(AngularVelocity)
	{};

	void Update(float deltatime);
};

