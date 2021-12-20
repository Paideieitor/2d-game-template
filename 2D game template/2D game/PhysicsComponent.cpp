#include "PhysicsComponent.h"
#include "Physics.h"

#include "BOX2D/Box2D/Box2D.h"
#pragma comment( lib, "BOX2D/libx86/Release/Box2D.lib" )

PhysicsComponent::PhysicsComponent(fpoint position, fpoint dimentions)
{
	SetPosition(position.x, position.y);
	SetVelocity(0, 0);
	SetAcceleration(0, 0);
	SetDimentions(dimentions.x, dimentions.y);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x,position.y);
	body = game->physics->world->CreateBody(&bodyDef);
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimentions.x, dimentions.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.45f;

	fixture = body->CreateFixture(&fixtureDef);
}

PhysicsComponent::~PhysicsComponent()
{
}


b2Body* PhysicsComponent::GetBody()
{
	return body;
}


void PhysicsComponent::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void PhysicsComponent::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void PhysicsComponent::SetAcceleration(float x, float y)
{
	acceleration.x = x;
	acceleration.y = y;
}

void PhysicsComponent::SetDimentions(float x, float y)
{
	dimentions.x = x;
	dimentions.y = y;
}

void PhysicsComponent::SetRotationAngle(float rotation)
{
	rotationAngle = rotation;
}
