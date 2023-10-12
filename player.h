#pragma once
#include "Point.h"

struct Renderer;

class Player
{
	//TODO make private
public:
	FPoint pos = {100,100};
	FPoint velocity{ 0,0 };
	float rotationAngle{ 0 };
	FPoint graphics[5] = { {0,-10},{-10,10}, {0,5}, {10,10},{0,-10} };

	float accelerationForce = 1;

	bool isAccelerating = false;


public:
	int Draw(Renderer& rend);
	void Update(float deltatime);
	void setAccelerating(bool b);
};

