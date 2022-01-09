#include "PhysicsComponent.h"
#include "Physics.h"
#include "Render.h"
#include "Textures.h"

#include "BOX2D/Box2D/Box2D.h"
/*
PhysicsComponent::PhysicsComponent(ColliderType type, b2BodyType bodyType, fpoint position, fpoint dimentions, float rotation, float density, float friction, float restitution, bool isSensor)
{
	 colliderType = type;

	 if(type ==ColliderType::BOX_COLLIDER)
	 {
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

		for (int i = 0; i < boxShape.GetVertexCount(); i++)
		{
			vertices.push_back(body->GetWorldPoint({ boxShape.GetVertex(i).x, boxShape.GetVertex(i).y }));
		}

	 }
	 else if (type == ColliderType::CIRCLE_COLLIDER)
	 {

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
	 else if (type == ColliderType::POLYGON_COLLIDER)
	 {

		 b2BodyDef bodyDef;
		 bodyDef.type = bodyType;
		 bodyDef.position.Set(position.x, position.y);
		 bodyDef.angle = rotation / 57.2958f;
		 body = game->physics->GetWorld()->CreateBody(&bodyDef);


		 b2Vec2 vertex[5];
		 vertex[0].Set(0.0f, 50.0f);
		 vertex[1].Set(130.0f, 0.0f);
		 vertex[2].Set(0.0f, 100.0f);
		 vertex[3].Set(140.0f, 140.0f);
		 vertex[4].Set(100.0f, 200.0f);

		 int32 count = 5;
		 b2PolygonShape polygon;
		 polygon.Set(vertex, count);

		 b2FixtureDef fixtureDef;
		 fixtureDef.shape = &polygon;
		 fixtureDef.density = density;
		 fixtureDef.friction = friction;
		 fixtureDef.restitution = restitution;
		 fixtureDef.isSensor = isSensor;
		 fixture = body->CreateFixture(&fixtureDef);

		 for (int i = 0; i < polygon.GetVertexCount(); i++)
		 {
			 vertices.push_back(body->GetWorldPoint({ polygon.GetVertex(i).x, polygon.GetVertex(i).y }));
		 }

	 }
	 else if (type == ColliderType::NONE)
	 {

	 }

}
*/
PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
}

fpoint PhysicsComponent::GetPosition()
{
	return {body->GetPosition().x,body->GetPosition().y};
}

fpoint PhysicsComponent::GetLinearVelocity()
{
	return {body->GetLinearVelocity().x, body->GetLinearVelocity().y};
}

float PhysicsComponent::GetAngularVelocity()
{
	return body->GetAngularVelocity();
}


float PhysicsComponent::GetRotation()
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

void PhysicsComponent::DebugDraw()
{
}



