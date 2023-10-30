#pragma once
#include "Drawable.h"
class Line : public Drawable
{
public:
	FPoint worldpoints[2] = {};

	Line(): Drawable((int)std::size(worldpoints), (int)offsetof(Line, worldpoints))
	{};
};
