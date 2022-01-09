#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H


#include "PhysicsComponent.h"
#include <vector>

class BoxCollider : public PhysicsComponent 
{
public:

	 BoxCollider(fpoint position, fpoint size, float rotation, b2BodyType bodyType, float density, float friction, float restitution, bool isSensor);
	 void DebugDraw() override;

private:
	void UpdateVertex();
	std::vector<b2Vec2> vertices;
};


#endif