#include "PhysicsComponent.h"
#include "Physics.h"
#include "Render.h"
#include "Textures.h"

#include "BOX2D/Box2D/Box2D.h"
#pragma comment( lib, "BOX2D/libx86/Release/Box2D.lib" )

PhysicsComponent::PhysicsComponent(ColliderType type, b2BodyType bodyType, fpoint position, fpoint dimentions)
{
	 if(type ==ColliderType::BOX_COLLIDER)
	 {
		SetPosition(position.x, position.y);
		SetDimentions(dimentions.x, dimentions.y);

		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position.Set(position.x, position.y);
		body = game->physics->GetWorld()->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(dimentions.x, dimentions.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0.4f;

		fixture = body->CreateFixture(&fixtureDef);
		debugTexture = game->textures->Load("images/test.png");
	 }
	 else if(type == ColliderType::NONE)
	 {
	 }

}

PhysicsComponent::~PhysicsComponent()
{
}

fpoint PhysicsComponent::GetDimentions()
{
	return dimentions;
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

void PhysicsComponent::DebugDraw()
{
	//very very wack right now
	debugTexture = game->textures->Load("images/test.png");

	if(debugTexture != nullptr)
	game->render->AddTextureEvent(5, debugTexture, { this->GetBody()->GetPosition().x - this->GetDimentions().x,-this->GetBody()->GetPosition().y - this->GetDimentions().y }, 0, 0, { (int)this->GetDimentions().x * 2, (int)this->GetDimentions().y * 2 }, false, 255, true, 1.0f, this->GetBody()->GetAngle() * 57.2958f, fpoint(this->GetDimentions().x / 2, this->GetDimentions().y / 2));
}


