#include "PhysicsComponent.h"
#include "Physics.h"
#include "Render.h"
#include "Textures.h"

#include "BOX2D/Box2D/Box2D.h"

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

PhysicsComponent::~PhysicsComponent()
{
}


b2Body* PhysicsComponent::GetBody()
{
	return body;
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
	rotationAngle = rotation / 57.2958f;
}

void PhysicsComponent::DebugDraw()
{
	DrawRectangle();
	for (int p = 0; p < vertices.size(); p++)
	{
		if (p == vertices.size() - 1)
		{
			game->render->RenderLine(5, { vertices[p].x,-vertices[p].y }, { vertices[0].x,-vertices[0].y }, { 255,0,0,255 });
		}
		else
		{
			game->render->RenderLine(5, { vertices[p].x,-vertices[p].y }, { vertices[p + 1].x,-vertices[p + 1].y }, { 255,0,0,255 });
		}
	}
}

void PhysicsComponent::DrawRectangle()
{
	b2PolygonShape* shape = nullptr;
	shape = GetVertex();
	if (shape != nullptr)
	{
		for (int i = 0; i < shape->GetVertexCount(); i++)
		{
			vertices[i] = body->GetWorldPoint({ shape->GetVertex(i).x, shape->GetVertex(i).y });
		}
	}
}

b2PolygonShape* PhysicsComponent::GetVertex()
{
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		b2Shape::Type shapeType = f->GetType();
		if (shapeType == b2Shape::e_circle)
		{
			b2CircleShape* circleShape = (b2CircleShape*)fixture->GetShape();
		}
		else if (shapeType == b2Shape::e_polygon)
		{
			b2PolygonShape* polygonShape = (b2PolygonShape*)fixture->GetShape();
			return polygonShape;
		}
	}
}

