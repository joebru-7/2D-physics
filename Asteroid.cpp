#include "Asteroid.h"

const FPoint Asteroid::graphics[8] = {{-8,-10},{-10,8},{-7,10},{10,10},{10,6},{2,6},{-4,-2},{-8,-10}};


void Asteroid::Update(float deltatime)
{
	constexpr int count = 8; //std::size(Asteroid{}.worldpoints);
	pos += velocity * deltatime;
	rotationAngle += AngularVelocity * deltatime;

	auto matrix = FMatrix(rotationAngle, pos);
	for (int i = 0; i < count; i++)
	{
		worldpoints[i] = matrix * graphics[i];
	}
}