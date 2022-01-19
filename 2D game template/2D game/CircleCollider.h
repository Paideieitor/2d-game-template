#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "PhysicsComponent.h"

class CircleCollider: public PhysicsComponent
{
public:

	CircleCollider(fpoint position, float radius, float rotation, b2BodyType bodyType, float density = 1.0f, float friction = 0.0f, float restitution = 0.15f, bool isSensor = false);
	void DebugDraw() override;

private:

	float radius;
};

#endif