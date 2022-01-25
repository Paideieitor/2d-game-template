#include "CircleCollider.h"
#include "PhysicsComponent.h"
#include "Physics.h"
#include "Game.h"
#include "Render.h"
#include "BOX2D/Box2D/Box2D.h"

CircleCollider::CircleCollider(fpoint position, float radius, float rotation, b2BodyType bodyType, float density, float friction, float restitution, bool isSensor)
{
	colliderType = ColliderType::CIRCLE_COLLIDER;

	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, position.y);
	body = game->physics->GetWorld()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = radius;
	this->radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.isSensor = isSensor;
	fixtureDef.userData = this;
	fixture = body->CreateFixture(&fixtureDef);
}

void CircleCollider::DebugDraw()
{
	game->render->RenderCircle(5, { body->GetPosition().x,-body->GetPosition().y }, radius, { 255,0,0,255 });
}
