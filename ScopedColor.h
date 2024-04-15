#pragma once
#include "sdl_wrappers.h"

class ScopedColor
{
	Color prevColor;
	Renderer& renderer;
public:
	ScopedColor(Color color, Renderer& renderer):renderer(renderer)
	{
		prevColor = renderer.getDrawColor();
		renderer.SetDrawColor(color);
	}
	ScopedColor(ScopedColor&) = delete;
	ScopedColor(ScopedColor&&) = delete;
	~ScopedColor()
	{
		renderer.SetDrawColor(prevColor);
	}
};

