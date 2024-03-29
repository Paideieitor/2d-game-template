#include "Physics.h"
#include "PhysicsComponent.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"
#include "Joint.h"
#include "DistanceJoint.h"
#include "RevoluteJoint.h"
#include "ContactListener.h"
#include "Input.h"

#include "BOX2D/Box2D/Box2D.h"
#ifdef NDEBUG
#pragma comment( lib, "BOX2D/libfiles/ReleaseBox2d/Box2D.lib" )
#else
#pragma comment( lib, "BOX2D/libfiles/DebugBox2d/Box2D.lib" )
#endif

Physics::Physics()
{
	CreateWorld(new b2Vec2(0.0f, gravity));

	//Collider listener
	listener = new ContactListener();
	world->SetContactListener(listener);
}

Physics::~Physics()
{

}

bool Physics::SetUp(pugi::xml_node&)
{
	return true; 
}

bool Physics::Update(float dt)
{

	float p = dt/(1.0f / 1000.0f);
	for(int x= 0; x < (int)p; x++)
	{
		world->Step(1.0f / 1000.0f, 6, 2);
	}


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
	for (size_t i = 0; i < physicsObjects.size(); ++i)
	{
		if(physicsObjects[i] == object)
		{
			delete physicsObjects[i];
			physicsObjects.erase(physicsObjects.begin() + i);
		}
	}
}

void Physics::AddJoint(Joint* joint)
{
	joints.push_back(joint);
}

void Physics::DestroyJoint(Joint* joint)
{
	for (size_t i = 0; i < joints.size(); ++i)
	{
		if (joints[i] == joint)
		{
			delete joints[i];
			joints.erase(joints.begin() + i);
		}
	}
}

void Physics::PhysicsDebugDraw()
{
	for(size_t i = 0; i < physicsObjects.size(); ++i)
	{
		physicsObjects[i]->DebugDraw();
	}
}


