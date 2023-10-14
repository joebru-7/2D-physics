#include "Asteroid.h"

int Asteroid::Draw(Renderer& rend)
{
	constexpr int count = std::size(Asteroid{}.worldpoints);
	return rend.DrawLines(worldpoints, count);
}

void Asteroid::Update(float deltatime)
{
	constexpr int count = std::size(Asteroid{}.worldpoints);
	pos += velocity * deltatime;
	rotationAngle += AngularVelocity * deltatime;

	auto matrix = FMatrix(rotationAngle, pos);
	for (int i = 0; i < count; i++)
	{
		worldpoints[i] = matrix * graphics[i];
	}
}