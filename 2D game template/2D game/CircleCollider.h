#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "PhysicsComponent.h"

class CircleCollider: public PhysicsComponent
{
public:

	CircleCollider(fpoint position, float radius, float rotation, BodyType type, float density = 1.0f, float friction = 0.0f, float restitution = 0.15f, bool isSensor = false, const char* tag = "");
	void DebugDraw() override;

private:

	float radius;
};

#endif