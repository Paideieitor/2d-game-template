#include "Physics.h"
#include "PhysicsComponent.h"

#include "BOX2D/Box2D/Box2D.h"
#pragma comment( lib, "BOX2D/libx86/Release/Box2D.lib" )

Physics::Physics()
{
	gravity = new b2Vec2(0.0f,-9.8f);
	world = new b2World(*gravity);

	// Create gorund
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -700.0f);
	groundBody = world->CreateBody(&groundBodyDef);
	
	//Make ground fixture (structure, the form of the object)
	b2PolygonShape groundBox;
	groundBox.SetAsBox(5000.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);



}

Physics::~Physics()
{

}

bool Physics::SetUp(pugi::xml_node&)
{
	box = new PhysicsComponent({400,0}, { 20,20 });
	box1 = new PhysicsComponent({410,2}, { 20,20 });
	box2 = new PhysicsComponent({402,6}, { 20,20 });
	return true;
}

bool Physics::Update(float dt)
{
	world->Step(0.0005f, 3, 3);
	return true;
}

bool Physics::CleanUp()
{
	delete world;
	delete gravity;
	return true;
}
