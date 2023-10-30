#pragma once
#include "sdl_wrappers.h"

#include <vector>
extern std::vector<FPoint> debug_points;


class Drawable
{
protected:
	int count = 8;
	//const FPoint* const graphics = nullptr;
	int OfsetOfworldpoints;

protected:
	Drawable() = default;
	Drawable(int count, int OfsetOfworldpoints)
		:count(count), OfsetOfworldpoints(OfsetOfworldpoints)
	{}

public:
	//virtual ~Drawable() = default;

	[[nodiscard]] SDL_FRect calculateBounds() const
	{
		SDL_FRect ret{};
		SDL_EncloseFPoints(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count, nullptr, &ret);
		return ret;
	}

	int Draw(Renderer& rend)
	{
		return rend.DrawLines(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count);
	}

	bool collidesWith(const Drawable& other)const 
	{
		FPoint* myWorldpoints = reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints);
		FPoint* otherWorldpoints = reinterpret_cast<FPoint*>((std::byte*)&other + other.OfsetOfworldpoints);

		for (auto i = 0; i < count-1; i++)
		{
			const FPoint& p1 = myWorldpoints[i];
			const FPoint& p2 = myWorldpoints[i + 1];
			for (auto j = 0; j < other.count-1; j++)
			{
				const FPoint& p3 = otherWorldpoints[j];
				const FPoint& p4 = otherWorldpoints[j + 1];

				const float denom = ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
				const float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x));
				const float u = ((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x));
			
				static_assert(std::numeric_limits<float>::is_iec559, "Please use IEEE754,denom might me 0");
				const float td = t / denom;
				const float ud = u / denom;
				//FPoint intersection = p1
				if (td >= 0 && td <= 1 && ud >= 0 && ud <= 1) 
				{
					return true;
				}

			}
		}
		return false;
	}
	
};