#pragma once
#include "sdl_wrappers.h"
#include "Rectangle.h"

class Drawable
{
protected:
	int count;
private:
	//const FPoint* const graphics = nullptr;
	int OfsetOfworldpoints;

protected:
	Drawable() = default;
	Drawable(int count, int OfsetOfworldpoints)
		:count(count), OfsetOfworldpoints(OfsetOfworldpoints)
	{}

public:
	//virtual ~Drawable() = default;

	[[nodiscard]] const FPoint* getPointArray() const
	{
		return reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints);
	} 

	[[nodiscard]] FPoint* getPointArray() 
	{
		return const_cast<FPoint*>(const_cast<const Drawable*>(this)->getPointArray());
	}

	[[nodiscard]] FRectangle calculateBounds() const
	{
		FRectangle ret{};
		SDL_EncloseFPoints(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count, nullptr, &ret);
		return ret;
	} 

	int Draw(Renderer& rend) const
	{
		return rend.DrawLines(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count);
	}

};