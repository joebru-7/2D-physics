#include "PhysicsBody.h"
#include "Hit.h"
#include <cmath>
#include <limits>
#include "Constants.h"

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
					float NormingVal = 1/std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
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

void PhysicsBody::applyForce(float force, FPoint direction)
{
	velocity += (direction * force) * (1 / mass);
}

void PhysicsBody::handleCollision(PhysicsBody& other, Hit hit) {
	// Resolve collision normal and calculate relative velocity
	FPoint relativeVelocity = {
		other.velocity.x - velocity.x,
		other.velocity.y - velocity.y
	};
	
	float velocityAlongNormal = relativeVelocity.x * hit.hitNormal.x + relativeVelocity.y * hit.hitNormal.y;

	// Check if objects are moving away from each other
	if (velocityAlongNormal > 0) return;

	// Calculate impulse
	float e = 0.9f; // Coefficient of restitution (for fully elastic collision)
	float j = -(1 + e) * velocityAlongNormal;
	j /= 1 / mass + 1 / other.mass;

	// Apply impulse to change velocities
	FPoint impulse = { j * hit.hitNormal.x, j * hit.hitNormal.y };
	velocity.x -= 1 / mass * impulse.x;
	velocity.y -= 1 / mass * impulse.y;
	if (other.isMovable)
	{
		other.velocity.x += 1 / other.mass * impulse.x;
		other.velocity.y += 1 / other.mass * impulse.y;
	}

	// Calculate relative velocity at the contact point
	FPoint relativeContactPosition = { pos.x - other.pos.x, pos.y - other.pos.y };
	float contactVelocityPerpendicular = -relativeContactPosition.x * angularVelocity + relativeContactPosition.y * angularVelocity;

	// Calculate impulse for angular velocity
	float angularImpulse = contactVelocityPerpendicular / (1 / mass + 1 / other.mass);

	// Apply impulse to change angular velocities
	angularVelocity -= angularImpulse / rotationalInertia;
	if (other.isMovable)
		other.angularVelocity += angularImpulse / other.rotationalInertia;
}

void PhysicsBody::Update(float DeltaTime)
{
	if (!isMovable)
		return;

	velocity += gravity * DeltaTime;
	pos += velocity * DeltaTime;
	rotationAngle += angularVelocity * DeltaTime;
}
