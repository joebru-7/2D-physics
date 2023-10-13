#include "Asteroid.h"

int Asteroid::Draw(Renderer& rend)
{
	constexpr int count = std::size(Asteroid{}.graphics);
	auto matrix = FMatrix(rotationAngle, pos);

	FPoint data[count]{};

	for (int i = 0; i < std::size(data); i++)
	{
		data[i] = matrix * graphics[i];
	}

	return rend.DrawLines(data, count);
}

void Asteroid::Update(float deltatime)
{
	pos += velocity * deltatime;
}