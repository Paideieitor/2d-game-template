#include "PhysicsComponent.h"
#include "Physics.h"
#include "Render.h"
#include "Textures.h"

#include "BOX2D/Box2D/Box2D.h"
#pragma comment( lib, "BOX2D/libfiles/ReleaseBox2d/Box2D.lib" )

PhysicsComponent::PhysicsComponent(ColliderType type, b2BodyType bodyType, fpoint position, fpoint dimentions, float rotation, float density, float friction, float restitution, bool isSensor)
{
	 if(type ==ColliderType::BOX_COLLIDER)
	 {
		SetPosition(position.x, position.y);
		SetDimentions(dimentions.x, dimentions.y);

		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.angle = rotation / 57.2958f;
		body = game->physics->GetWorld()->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(dimentions.x, dimentions.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		fixtureDef.isSensor = isSensor;
		fixture = body->CreateFixture(&fixtureDef);

	 }
	 else if (type == ColliderType::CIRCLE_COLLIDER)
	 {
		 SetPosition(position.x, position.y);
		 SetDimentions(dimentions.x, dimentions.y);

		 b2BodyDef bodyDef;
		 bodyDef.type = bodyType;
		 bodyDef.position.Set(position.x, position.y);
		 body = game->physics->GetWorld()->CreateBody(&bodyDef);

		 b2CircleShape circle;
		 circle.m_p.Set(position.x, position.y);
		 circle.m_radius = 0.5f;

		 b2FixtureDef fixtureDef;
		 fixtureDef.shape = &circle;
		 fixtureDef.density = density;
		 fixtureDef.friction = friction;
		 fixtureDef.restitution = restitution;
		 fixtureDef.isSensor = isSensor;
		 fixture = body->CreateFixture(&fixtureDef);
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
	test = game->textures->Load("images/test.png");
		game->render->RenderTexture(5, test, { this->GetBody()->GetPosition().x - this->GetDimentions().x,-this->GetBody()->GetPosition().y - this->GetDimentions().y/2 }, 0, 0, { (int)this->GetDimentions().x * 2, (int)this->GetDimentions().y * 2 }, false, 255, true, 1.0f, -(this->GetBody()->GetAngle() * 57.2958f), fpoint(this->GetDimentions().x, this->GetDimentions().y));
		
		//fpoint* point1 = new fpoint(this->GetBody()->GetPosition().x - (this->GetDimentions().x / 2),-this->GetBody()->GetPosition().y - (this->GetDimentions().y / 2));
		//fpoint* point2 = new fpoint(this->GetBody()->GetPosition().x + (this->GetDimentions().x / 2), -this->GetBody()->GetPosition().y + (this->GetDimentions().y / 2));
		//
		//float angle = -this->GetBody()->GetAngle();
		//
		//fpoint* pointP = new fpoint(point1->x* cos(angle) - point1->y * sin(angle), point1->y * cos(angle) + point1->x * sin(angle));
		//fpoint* pointK = new fpoint(point2->x * cos(angle) - point2->y * sin(angle), point2->y * cos(angle) + point2->x * sin(angle));
		//
		//game->render->AddLineEvent(5, *pointP , *pointK , { 255,0,0,255 });
		//
		//delete point1;
		//delete point2;
		//delete pointP;
		//delete pointK;
}		//

void PhysicsComponent::DrawRectangle()
{

}


