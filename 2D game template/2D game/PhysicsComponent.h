#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Point.h"
#include "Color.h"
#include <vector>

class b2Body;
class b2Fixture;
class Texture;
class b2PolygonShape;
enum  b2BodyType;
struct b2Vec2;
struct Color;

enum ColliderType
{
BOX_COLLIDER,
POLYGON_COLLIDER,
CIRCLE_COLLIDER,
NONE
};

enum BodyType {
DYNAMIC,
KINEMATIC,
STATIC
};

class PhysicsComponent
{
public:

	PhysicsComponent();
	virtual ~PhysicsComponent();

	const fpoint GetPosition() const;

	fpoint GetLinearVelocity();
	float GetAngularVelocity();
	const float GetRotation() const;

	void SetPosition(float x, float y);
	void SetLinearVelocity(float x, float y);
	void SetAngularVelocity(float velocity);
	void SetRotationAngle(float rotation);
	void SetLinearDump(float dump);
	void ApplyForce(fpoint force, bool wake);
	void ApplyLinearImpulse(fpoint linearImpulse, bool wake);
	void SetTag(const char* tag);
	const char* GetTag();
	b2Body* GetBody();

	ColliderType colliderType = ColliderType::NONE;

	virtual void DebugDraw();

	bool inVine;

	std::vector<PhysicsComponent*> contacts;

protected:	
	Color color = { 0,255,255,255 };
	const char* tag;
	b2Body* body;
	b2Fixture* fixture;
};

#endif
