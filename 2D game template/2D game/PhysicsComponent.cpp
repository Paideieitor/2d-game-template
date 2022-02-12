#include "PhysicsComponent.h"
#include "Physics.h"
#include "Render.h"
#include "Textures.h"

#include "BOX2D/Box2D/Box2D.h"

PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
	body->DestroyFixture(fixture);
	game->physics->GetWorld()->DestroyBody(body);
}

fpoint PhysicsComponent::GetLinearVelocity()
{
	return {body->GetLinearVelocity().x, body->GetLinearVelocity().y};
}

float PhysicsComponent::GetAngularVelocity()
{
	return body->GetAngularVelocity();
}

const fpoint PhysicsComponent::GetPosition() const
{
	b2Vec2 pos = body->GetPosition();
	return fpoint((float)pos.x, (float)-pos.y);
}

const float PhysicsComponent::GetRotation() const
{
	return body->GetAngle() * 57.2958f;
}


void PhysicsComponent::SetPosition(float x, float y)
{
	body->SetTransform({x,y},body->GetAngle());
}

void PhysicsComponent::SetLinearVelocity(float x, float y)
{
	body->SetLinearVelocity({x,y});
}

void PhysicsComponent::SetAngularVelocity(float velocity)
{
	body->SetAngularVelocity(velocity);
}

void PhysicsComponent::SetRotationAngle(float rotation)
{
	body->SetTransform({ body->GetPosition().x,body->GetPosition().y}, rotation / 57.2958f);
}

void PhysicsComponent::ApplyForce(fpoint force, bool wake)
{
	body->ApplyForceToCenter(b2Vec2(force.x, force.y), wake);
}

void PhysicsComponent::ApplyLinearImpulse(fpoint linearImpulse, bool wake)
{
	body->ApplyLinearImpulse(b2Vec2(linearImpulse.x, linearImpulse.y), body->GetWorldCenter(), wake);
}

void PhysicsComponent::SetTag(const char* tag)
{
	this->tag = tag;
}

const char* PhysicsComponent::GetTag()
{
	return tag;
}

b2Body* PhysicsComponent::GetBody()
{
	return body;
}

void PhysicsComponent::DebugDraw()
{
}