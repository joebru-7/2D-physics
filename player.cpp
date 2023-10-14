#include "player.h"
#include "sdl_wrappers.h"

int Player::Draw(Renderer& rend)
{
	constexpr int count = std::size(Player{}.graphics);
	return rend.DrawLines(worldpoints, count);
}

void Player::Update(float deltatime)
{
	if (isAccelerating)
		velocity += FromAngle(rotationAngle, accelerationForce * deltatime);
	pos += velocity * deltatime;

	constexpr int count = std::size(Player{}.graphics);
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
