#pragma once
#include "Point.h"
#include "sdl_wrappers.h"
#include "Drawable.h"

class Player :public Drawable
{
	//TODO make private
public:
	FPoint pos = {100,100};
	FPoint velocity{ 0,0 }; //px/s
	float rotationAngle{ 0 }; //rad
	FPoint graphics[5] = { {0,-10},{-10,10}, {0,5}, {10,10},{0,-10} };
	FPoint worldpoints[5]{};

	float accelerationForce = 10;

	bool isAccelerating = false;
	bool isBreaking = false;
	
public:
	Player() :Drawable(5, offsetof(Player, worldpoints))
	{};

	//int Draw(Renderer& rend);
	void Update(float deltatime);
	void setAccelerating(bool b);
	void setBreaking(bool b);
};

