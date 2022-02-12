#ifndef POLYGONCOLLIDER_H
#define POLYGONCOLLIDER_H

#include "PhysicsComponent.h"
#include <vector>
class PolygonCollider : public PhysicsComponent
{
public:

	PolygonCollider(fpoint position,int numOfVertex, b2Vec2 vertex[], float rotation, BodyType type, float density, float friction, float restitution, bool isSensor, const char* tag);
	void DebugDraw();

private:
	void UpdateVertex();
	std::vector<b2Vec2> vertices;
};

#endif