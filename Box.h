#pragma once
#include "Drawable.h"
#include "PhysicsBody.h"
#include "Constants.h"

class Box : public PhysicsBody
{
public:
	
	FPoint worldpoints[5] = {};
	static constexpr FPoint graphics[5] = { {10,10}, {10,-10}, {-10,-10}, {-10,10}, {10,10} };


	Box() : PhysicsBody((int)std::size(worldpoints), (int)offsetof(Box, worldpoints)) {}
	Box(FPoint pos) : PhysicsBody(pos,(int)std::size(worldpoints), (int)offsetof(Box, worldpoints)) {}

	void Update(float DeltaTime)
	{
		constexpr int count = 5; // std::size(Asteroid{}.worldpoints);
		velocity += gravity * DeltaTime;
		pos += velocity * DeltaTime;
		rotationAngle += angularVelocity * DeltaTime;

		auto matrix = FMatrix(rotationAngle, pos, scale);
		for (int i = 0; i < count; i++)
		{
			worldpoints[i] = matrix * graphics[i];
		}
	}

};

