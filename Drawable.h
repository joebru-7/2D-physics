#pragma once
#include "sdl_wrappers.h"
#include "Rectangle.h"

class Drawable
{
protected:
	int count;
	//const FPoint* const graphics = nullptr;
	int OfsetOfworldpoints;

protected:
	Drawable() = default;
	Drawable(int count, int OfsetOfworldpoints)
		:count(count), OfsetOfworldpoints(OfsetOfworldpoints)
	{}

public:
	//virtual ~Drawable() = default;

	[[nodiscard]] FPoint* getPointArray()
	{
		return reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints);
	}

	[[nodiscard]] virtual FRectangle calculateBounds() const
	{
		FRectangle ret{};
		SDL_EncloseFPoints(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count, nullptr, &ret);
		return ret;
	} 

	int Draw(Renderer& rend) const
	{
		return rend.DrawLines(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count);
	}

	bool collidesWith(const Drawable& other, struct Hit* hitResult = nullptr) const;
	
	
};