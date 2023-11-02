#pragma once
#include "Point.h"
#include "Rectangle.h"

class BulletQuadTree
{
	struct QuadNode
	{
		FPoint maxCorner;
		FPoint minCorner;
		bool isLeaf;
		QuadNode* children[4];
		std::optional<Bullet> value;

		void getOverlaps(FRectangle rect, std::vector<Bullet*>& dest)
		{
			if (isLeaf)
			{
				dest.push_back(&*value);
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					children[i]->getOverlaps(rect, dest);
				}
			}
		};

		void UpdateAll(float deltaTime)
		{
			//TODO: check movemnet and reallocate
			if (isLeaf)
			{
				value->Update(deltaTime);
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					children[i]->UpdateAll(deltaTime);
				}
			}
		}

		void Insert(Bullet t, FRectangle bounds)
		{
			if (isLeaf)
			{
				//also push value
			}
			// push t
		}

	};

	QuadNode root{};
	
	std::vector<Bullet*> overlaps{};

public:
	std::span<Bullet*> getOverlaps(FRectangle rect)
	{
		overlaps.clear();
		root.getOverlaps(rect, overlaps);
		return overlaps;
	}

	void UpdateAll(float deltaTime)
	{
		return root.UpdateAll(deltaTime);
	}

	void Insert(Bullet t)
	{
		root.Insert(t,t.calculateBounds());
	}

};

