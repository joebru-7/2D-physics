#pragma once
#include "Drawable.h"

constexpr FPoint gravity{ 0,2 };//px/s/s

class Box : public Drawable
{
public:
	FPoint pos = { 100,100 };
	FPoint velocity{ 0,0 }; //px/s
	float rotationAngle{ 0 };//rad
	float AngularVelocity{ 0 };//rad/s
	float scale{ 1 };
	FPoint worldpoints[5] = {};
	static constexpr FPoint graphics[5] = { {10,10}, {10,-10}, {-10,-10}, {-10,10}, {10,10} };


	Box() : Drawable((int)std::size(worldpoints), (int)offsetof(Box, worldpoints)) {}
	Box(FPoint pos) : pos{ pos }, Drawable((int)std::size(worldpoints), (int)offsetof(Box, worldpoints)) {}

	void Update(float DeltaTime)
	{
		constexpr int count = 5; // std::size(Asteroid{}.worldpoints);
		velocity += gravity * DeltaTime;
		pos += velocity * DeltaTime;
		rotationAngle += AngularVelocity * DeltaTime;

		auto matrix = FMatrix(rotationAngle, pos, scale);
		for (int i = 0; i < count; i++)
		{
			worldpoints[i] = matrix * graphics[i];
		}
	}

};

