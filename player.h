#pragma once
#include "Point.h"
#include "sdl_wrappers.h"

class Player
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


public:
	int Draw(Renderer& rend);
	void Update(float deltatime);
	void setAccelerating(bool b);
};

