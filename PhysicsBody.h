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
	float mass = 1;

protected:
	PhysicsBody() = default;
	PhysicsBody(int Linecount, int OfsetOfworldpoints) : Drawable(Linecount, OfsetOfworldpoints) {}
	PhysicsBody(FPoint position, int Linecount, int OfsetOfworldpoints) : pos(position),Drawable(Linecount,OfsetOfworldpoints) {}
public:
	bool collidesWith(const PhysicsBody& other, struct Hit* hitResult)const;
	void applyForce(float force, FPoint worldpos);
};
