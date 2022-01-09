#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "PhysicsComponent.h"

class CircleCollider: public PhysicsComponent
{
public:

	CircleCollider(fpoint position, float radius, float rotation, b2BodyType bodyType, float density, float friction, float restitution, bool isSensor);
	void DebugDraw() override;

private:

	float radius;
};

#endif