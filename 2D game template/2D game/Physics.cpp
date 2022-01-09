#include "Physics.h"
#include "PhysicsComponent.h"
#include "BoxCollider.h"
#include "Input.h"

#include "BOX2D/Box2D/Box2D.h"
#ifdef NDEBUG
#pragma comment( lib, "BOX2D/libfiles/ReleaseBox2d/Box2D.lib" )
#else
#pragma comment( lib, "BOX2D/libfiles/DebugBox2d/Box2D.lib" )
#endif

Physics::Physics()
{
	CreateWorld(&b2Vec2(0.0f, gravity));
}

Physics::~Physics()
{

}

bool Physics::SetUp(pugi::xml_node&)
{
	AddPhysicsObject(new BoxCollider({60,60}, {100,100},0, b2BodyType::b2_dynamicBody,1.0f,1.0f,1.0f,false));
	return true;
}

bool Physics::Update(float dt)
{
	world->Step(0.0008f, 3, 3);
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

void Physics::DestroyPhysicsObject(PhysicsComponent* object)
{



}

void Physics::PhysicsDebugDraw()
{
	for(size_t i = 0; i < physicsObjects.size(); ++i)
	{
		physicsObjects[i]->DebugDraw();
	}
}


