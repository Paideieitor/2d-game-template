#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Point.h"
#include <vector>
#include <memory> // for the shared pointer, erase when no texture
class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class b2Body;
class b2Fixture;
class Texture;
class b2PolygonShape;
enum  b2BodyType;
struct b2Vec2;

enum ColliderType
{
BOX_COLLIDER,
POLYGON_COLLIDER,
CIRCLE_COLLIDER,
NONE
};


class PhysicsComponent
{
public:

	PhysicsComponent();
	virtual ~PhysicsComponent();

	fpoint GetPosition();
	fpoint GetLinearVelocity();
	float GetAngularVelocity();
	float GetRotation();


	void SetPosition(float x, float y);
	void SetLinearVelocity(float x, float y);
	void SetAngularVelocity(float velocity);
	void SetRotationAngle(float rotation);

	ColliderType colliderType = ColliderType::NONE;

	virtual void DebugDraw();

protected:	

	b2Body* body;
	b2Fixture* fixture;

};

#endif
