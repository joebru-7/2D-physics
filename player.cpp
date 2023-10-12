#include "player.h"
#include "sdl_wrappers.h"

int Player::Draw(Renderer& rend)
{
	constexpr int count = std::size(Player{}.graphics);
	auto matrix = FMatrix(rotationAngle, pos);

	FPoint data[count]{};

	for (int i = 0; i < std::size(data);  i++)
	{
		data[i] = matrix * graphics[i];
	}

	return rend.DrawLines(data, count);
}

void Player::Update(float deltatime)
{
	if(isAccelerating)
		velocity += FromAngle(rotationAngle, accelerationForce * deltatime);
	pos += velocity * deltatime;
}

void Player::setAccelerating(bool b)
{
	isAccelerating = b;
}
