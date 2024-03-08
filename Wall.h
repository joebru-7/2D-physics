#pragma once
#include "PhysicsBody.h"
class Wall : public PhysicsBody
{

	FPoint worldpoints[5] = {};
	//static constexpr FPoint graphics[5] = { {10,10}, {10,-10}, {-10,-10}, {-10,10}, {10,10} };

public:
	Wall(FPoint topcorner, float width, float height) : PhysicsBody((int)std::size(worldpoints), (int)offsetof(Wall, worldpoints))
	{
		worldpoints[0] = worldpoints[4] = topcorner;
		worldpoints[1] = topcorner + FPoint{ width,0.f };
		worldpoints[2] = topcorner + FPoint{ width,height };
		worldpoints[3] = topcorner + FPoint{ 0.f, height };
		mass = 10000; //lots
		isMovable = false;
	}
};

