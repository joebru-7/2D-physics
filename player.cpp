#include "player.h"
#include "sdl_wrappers.h"


void Player::Update(float deltatime)
{
	if (isAccelerating)
		velocity += FromAngle(rotationAngle, accelerationForce * deltatime);
	pos += velocity * deltatime;

	auto matrix = FMatrix(rotationAngle, pos);

	for (int i = 0; i < count; i++)
	{
		worldpoints[i] = matrix * graphics[i];
	}
}

void Player::setAccelerating(bool b)
{
	isAccelerating = b;
}
