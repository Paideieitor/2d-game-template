#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H


#include "PhysicsComponent.h"
#include <vector>

class BoxCollider : public PhysicsComponent 
{
public:

	 BoxCollider(fpoint position, fpoint size, float rotation,BodyType type, float density, float friction, float restitution,bool fixedRotation, bool isSensor, const char* tag);
	 void DebugDraw() override;
	void ChangeFixture(fpoint size, float density, float friction, float restitution, bool isSensor);

private:
	void UpdateVertex();
	std::vector<b2Vec2> vertices;

};


#endif