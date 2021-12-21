#include "Physics.h"
#include "PhysicsComponent.h"

#include "BOX2D/Box2D/Box2D.h"
#pragma comment( lib, "BOX2D/libx86/Release/Box2D.lib" )

Physics::Physics()
{
	CreateWorld(&b2Vec2(0.0f, gravity));
	CreateGround();
}

Physics::~Physics()
{

}

bool Physics::SetUp(pugi::xml_node&)
{
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 401,3 }, { 20,23 }));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 400,2 }, { 15,20 }));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 402,6 }, { 20,44 }));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_staticBody, { 0,-700 }, { 5000,20 }));
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

void Physics::CreateGround()
{
	// Create gorund
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -700.0f);
	groundBodyDef.type = b2BodyType::b2_staticBody;
	groundBody = world->CreateBody(&groundBodyDef);

	//Make ground fixture (structure, the form of the object)
	b2PolygonShape groundBox;
	groundBox.SetAsBox(5000.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 1.0f);
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


