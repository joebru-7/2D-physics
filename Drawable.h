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
	virtual ~Drawable() = default;

	virtual int Draw(Renderer& rend)
	{
		return rend.DrawLines(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count);
	}

	virtual bool collidesWith(const Drawable& other)const 
	{
		bool flag = false;

		FPoint* myWorldpoints = reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints);
		FPoint* otherWorldpoints = reinterpret_cast<FPoint*>((std::byte*)&other + other.OfsetOfworldpoints);

		for (auto i = 0; i < count-1; i++)
		{
			FPoint p1 = myWorldpoints[i];
			FPoint p2 = myWorldpoints[i + 1];
			for (auto j = 0; j < other.count-1; j++)
			{
				FPoint p3 = otherWorldpoints[j];
				FPoint p4 = otherWorldpoints[j + 1];

				float denom = ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
				float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x));
				float u = ((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x));
			
				float td = t / denom;
				float ud = u / denom;
				//FPoint intersection = p1
				if (td >= 0 && td <= 1 && ud >= 0 && ud <= 1) 
				{
					flag=true;
				}

			}
		}
		return flag;
	}
	
};