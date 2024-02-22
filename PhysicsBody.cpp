#include "PhysicsBody.h"
#include "Hit.h"
#include <cmath>

bool PhysicsBody::collidesWith(const PhysicsBody& other, Hit* hitResult)const
{
	if (!calculateBounds().isIntersecting(other.calculateBounds()))
		return false;

	const FPoint* myWorldpoints = this->getPointArray();
	const FPoint* otherWorldpoints = other.getPointArray();

	//Exact
	for (auto i = 0; i < count - 1; i++)
	{
		const FPoint& p1 = myWorldpoints[i];
		const FPoint& p2 = myWorldpoints[i + 1];
		for (auto j = 0; j < other.count - 1; j++)
		{
			const FPoint& p3 = otherWorldpoints[j];
			const FPoint& p4 = otherWorldpoints[j + 1];

			const float denom = ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
			const float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x));
			const float u = ((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x));

			static_assert(std::numeric_limits<float>::is_iec559, "Please use IEEE754,denom might me 0");
			const float td = t / denom;
			const float ud = u / denom;

			if (td >= 0 && td <= 1 && ud >= 0 && ud <= 1)
			{
				if (hitResult)
				{
					//multiple hits?
					FPoint collisionPoint = {
						p1.x + td * (p2.x - p1.x),
						p1.y + td * (p2.y - p1.y),
					};
					float NormingVal = std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
					FPoint normal = {
						-(p1.x - p2.x) * NormingVal,
						 (p1.y - p2.y) * NormingVal,
					};
					*hitResult = { .location = collisionPoint,.hitNormal=normal,.object1 = this, .segment1 = &p1, .object2 = &other, .segment2 = &p3 };
				}
				return true;
			}

		}
	}
	return false;
}

void PhysicsBody::applyForce(float force, FPoint worldpos)
{
	
}
