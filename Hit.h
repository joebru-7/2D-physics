#pragma once
#include "Point.h"
#include "Drawable.h"
struct Hit
{
	FPoint location;
	FPoint hitNormal;
	const PhysicsBody* object1;
	const FPoint* segment1;
	const PhysicsBody* object2;
	const FPoint* segment2;

};
