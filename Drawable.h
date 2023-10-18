#pragma once
#include "sdl_wrappers.h"

class Drawable
{
protected:
	FPoint pos = { 100,100 };
	float rotationAngle{ 0 };//rad
	int count = 8;
	//const FPoint* const graphics = nullptr;
	int OfsetOfworldpoints;

public:
	Drawable() = default;
	Drawable(FPoint pos, float rotationAngle, int count, int OfsetOfworldpoints)
		:pos(pos),rotationAngle(rotationAngle),count(count), OfsetOfworldpoints(OfsetOfworldpoints)
	{}
	
	virtual ~Drawable() = default;

	virtual int Draw(Renderer& rend)
	{
		return rend.DrawLines(reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints), count);
	}

	virtual bool collides(const Drawable& other)const 
	{
		FPoint* myWorldpoints = reinterpret_cast<FPoint*>((std::byte*)this + OfsetOfworldpoints);
		FPoint* otherWorldpoints = reinterpret_cast<FPoint*>((std::byte*)&other + OfsetOfworldpoints);

		for (auto i = 0; i < count-1; i++)
		{
			FPoint& p1 = myWorldpoints[i];
			FPoint& p2 = myWorldpoints[i + 1];
			for (auto j = 0; j < other.count-1; j++)
			{
				FPoint& p3 = otherWorldpoints[j];
				FPoint& p4 = otherWorldpoints[j + 1];

				float denom = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
				float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x))/denom;
				float u = ((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x)) / denom;
				
				//FPoint intersection = p1
				if (t >= 0 && t <= 1 && u >= 0 && u <= 1) 
				{
					return true;
				}

			}
		}
		return false;
	}
	
};