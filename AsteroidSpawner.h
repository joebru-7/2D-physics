#pragma once
#include <random>
#include "Asteroid.h"

class AsteroidSpawner
{
	std::random_device rd;
	std::default_random_engine en{ rd() };

	std::uniform_int_distribution<int>  heightDistribution;
	std::uniform_int_distribution<int>  widhtDistribution;
	std::uniform_real_distribution<float> angleDistribution{ 0.0f,6.28f };
	std::uniform_real_distribution<float>  speedDistribution{ 1.f,20.f };

public:
	AsteroidSpawner(int windowHeight, int windowWidth):heightDistribution{0,windowHeight}, widhtDistribution{0,windowWidth}
	{}

	Asteroid Create()
	{
		return Asteroid(
			FPoint{ (float)widhtDistribution(en),(float)heightDistribution(en) },
			FromAngle(angleDistribution(en), speedDistribution(en)),
			(float)angleDistribution(en),
			speedDistribution(en) * (heightDistribution(en) % 2 == 0 ? 1 : -1),
			(float)angleDistribution(en)
		);
	}
};

