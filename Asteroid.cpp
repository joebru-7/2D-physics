#include "Asteroid.h"

const FPoint Asteroid::graphics[asteroid_point_amount] =
//{ {7,8},{7,-8},{-9,-8},{-7,8},{7,8} };
{{-8,-10},{-10,8},{-7,10},{10,10},{10,6},{2,6},{-4,-2},{-8,-10}};


Asteroid Asteroid::Split()
{
	scale *= .5;
	return Asteroid(pos, velocity*-1, rotationAngle, -AngularVelocity, scale);
}

void Asteroid::Update(float deltatime)
{
	constexpr int count = asteroid_point_amount; // std::size(Asteroid{}.worldpoints);
	pos += velocity * deltatime;
	rotationAngle += AngularVelocity * deltatime;

	auto matrix = FMatrix(rotationAngle, pos, scale);
	for (int i = 0; i < count; i++)
	{
		worldpoints[i] = matrix * graphics[i];
	}
}