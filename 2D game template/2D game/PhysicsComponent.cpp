#include "PhysicsComponent.h"

#include "BOX2D/Box2D/Box2D.h"
#pragma comment( lib, "BOX2D/libx86/Release/Box2D.lib" )

PhysicsComponent::PhysicsComponent()
{
	SetPosition(0, 0);
	SetVelocity(0, 0);
	SetAcceleration(0, 0);
}

fpoint PhysicsComponent::GetPosition()
{
	return position;
}

fpoint PhysicsComponent::GetVelocity()
{
	return velocity;
}

fpoint PhysicsComponent::GetAcceleration()
{
	return acceleration;
}

float PhysicsComponent::GetRotationAngle()
{
	return rotationAngle;
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

void PhysicsComponent::SetRotationAngle(float rotation)
{
	rotationAngle = rotation;
}
