#pragma once
#include "Point.h"
#include "Rectangle.h"

constexpr int maxBullets = 2;
constexpr int maxDepth = 8;

template <typename T>
class QuadTree
{
	FRectangle extents;
public:
	QuadTree(FRectangle extents) :extents(extents),root(extents,nullptr) {}
	QuadTree(const QuadTree&) = delete;
	QuadTree(QuadTree&&) = delete;

private:
	struct QuadNode
	{
		FRectangle bounds;
		FPoint midpoint;
		std::unique_ptr<QuadNode> children[4]{};
		QuadNode* parent;
		std::vector<T> values;
		int depth = 0;

		QuadNode(FRectangle bounds, QuadNode* parent) :bounds{ bounds }, parent{ parent }
		{
			midpoint = { bounds.x + bounds.w * .5f , bounds.y + bounds.h * .5f };
			depth = parent ? parent->depth + 1 : 0;
		}

		void getOverlaps(FRectangle rect, std::vector<T>& dest)
		{
			if (!rect.isIntersecting(bounds))
				return;

			for(auto value: values)
			{
				if(value->bounds.isIntersecting(rect))
					dest.push_back(&*value);
			}

			for (int i = 0; i < 4; i++)
			{
				if(children[i]&&rect.isIntersecting(children[i]->bounds))
					children[i]->getOverlaps(rect, dest);
			}
			
		};

		QuadNode& getOrCreateChild(FPoint p)
		{
			bool below = p.y < midpoint.y;
			bool left = p.x < midpoint.x;
			int index  = (left) << 1 & (int)(below);
			if (children[index] == nullptr)
			{
				FPoint myRelevantOuterCorner = { bounds.x + left ? 0 : bounds.w,bounds.y + below ? 0 : bounds.h };
				children[index] = std::make_unique<QuadNode>(QuadNode(FRectangle({ midpoint,myRelevantOuterCorner }), this));
			}
			return *children[index];
		}

		QuadNode* GetChild(const FPoint& p)
		{
			bool below = p.y < midpoint.y;
			bool left = p.x < midpoint.x;
			int index = (left) << 1 & (int)(below);
			return children[index].get();
		}

		void Insert(T b)
		{
			if (depth == maxDepth)
			{
				values.push_back(b);
			}
			else
			{
				auto& child = getOrCreateChild(b->worldpoints[0]);
				auto bulletBounds = b->calculateBounds();

				if (child.bounds.isContaining(bulletBounds))
					return child.Insert(b);
				else
					values.push_back(b);
			}
		}

		void Clear()
		{
			values.clear();
			for (size_t i = 0; i < 4; i++)
			{
				if (children[i])
					children[i]->Clear();
			}
		}
	};

	QuadNode root;


private:
	std::vector<T> overlaps{};
public:
	std::span<T> getOverlaps(FRectangle rect)
	{
		overlaps.clear();
		root.getOverlaps(rect, overlaps);
		return overlaps;
	}

	void Clear()
	{
		root.Clear();
	}

	void Insert(T t)
	{
		return root.Insert(t);
	}


};

