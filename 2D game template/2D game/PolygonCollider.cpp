#include "PolygonCollider.h"
#include "PhysicsComponent.h"
#include "Physics.h"
#include "Game.h"
#include "Render.h"
#include "BOX2D/Box2D/Box2D.h"

PolygonCollider::PolygonCollider(fpoint position, int numOfVertex, b2Vec2 vertex[], float rotation, BodyType type, float density, float friction, float restitution, bool isSensor)
{
	colliderType = ColliderType::POLYGON_COLLIDER;

	b2BodyDef bodyDef;
	switch (type)
	{
	case BodyType::DYNAMIC:
		bodyDef.type = b2BodyType::b2_dynamicBody;
		break;
	case BodyType::KINEMATIC:
		bodyDef.type = b2BodyType::b2_kinematicBody;
		break;
	case BodyType::STATIC:
		bodyDef.type = b2BodyType::b2_staticBody;
		break;
	}
	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = rotation / 57.2958f;
	body = game->physics->GetWorld()->CreateBody(&bodyDef);

	b2PolygonShape polygon;
	polygon.Set(vertex, numOfVertex);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygon;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.isSensor = isSensor;
	fixtureDef.userData = this;
	fixture = body->CreateFixture(&fixtureDef);

	for (int i = 0; i < polygon.GetVertexCount(); i++)
	{
		vertices.push_back(body->GetWorldPoint({ polygon.GetVertex(i).x, polygon.GetVertex(i).y }));
	}
}

void PolygonCollider::DebugDraw()
{
	UpdateVertex();
	for (size_t p = 0; p < vertices.size(); p++)
		if (p == vertices.size() - 1)
			game->render->RenderLine(false, 5, { vertices[p].x,-vertices[p].y }, { vertices[0].x,-vertices[0].y }, { 255,0,0,255 }, true);
		else
			game->render->RenderLine(false, 5, { vertices[p].x,-vertices[p].y }, { vertices[p + 1].x,-vertices[p + 1].y }, { 255,0,0,255 }, true);
}

void PolygonCollider::UpdateVertex()
{
	b2PolygonShape* shape = nullptr;

	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		b2Shape::Type shapeType = f->GetType();
		if (shapeType == b2Shape::e_polygon)
		{
			shape = (b2PolygonShape*)fixture->GetShape();
		}
	}

	if (shape != nullptr)
	{
		for (int i = 0; i < shape->GetVertexCount(); i++)
		{
			vertices[i] = body->GetWorldPoint({ shape->GetVertex(i).x, shape->GetVertex(i).y });
		}
	}
}
