#include "Physics.h"
#include "PhysicsComponent.h"

#include "BOX2D/Box2D/Box2D.h"
#pragma comment( lib, "BOX2D/libx86/Release/Box2D.lib" )

Physics::Physics()
{
	CreateWorld(&b2Vec2(0.0f, gravity));
}

Physics::~Physics()
{

}

bool Physics::SetUp(pugi::xml_node&)
{
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 400,3 }, { 40,23 },1.0f,0.3f,0.82f));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 490,2 }, { 15,30 }, 1.0f, 0.3f, 0.42f));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 540,90 }, { 23,44 }, 1.0f, 0.3f, 0.62f));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 540,20 }, { 23,44 }, 1.0f, 0.3f, 0.22f));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_staticBody, { 40,-1000 }, { 5000,20 }, 1.0f, 0.3f, 0.72f));
	return true;
}

bool Physics::Update(float dt)
{
	world->Step(0.001f, 3, 3);
	return true;
}

bool Physics::CleanUp()
{
	delete world;
	return true;
}

b2World* Physics::GetWorld()
{
	return world;
}

void Physics::CreateWorld(b2Vec2* gravity)
{
	world = new b2World(*gravity);
}

void Physics::AddPhysicsObject(PhysicsComponent* object)
{
	physicsObjects.push_back(object);
}

void Physics::PhysicsDebugDraw()
{
	for(int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObjects[i]->DebugDraw();
	}
}


