#pragma once
#include "Drawable.h"

class PhysicsBody : public Drawable
{
public:
	FPoint pos = { 100,100 };
	FPoint velocity{ 0,0 }; //px/s
	float rotationAngle{ 0 };//rad
	float AngularVelocity{ 0 };//rad/s
	float scale{ 1 };

	bool collidesWith(const PhysicsBody& other, Hit* hitResult)const;
};
