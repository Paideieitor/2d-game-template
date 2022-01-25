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
	CreateWorld(&b2Vec2(0.0f, gravity));

	//Collider listener
	listener = new ContactListener();
	world->SetContactListener(listener);
}

Physics::~Physics()
{

}

bool Physics::SetUp(pugi::xml_node&)
{
	b2Vec2 vertices[3];
	vertices[0] = { 0,0 };
	vertices[1] = { 50,0 };
	vertices[2] = { 25,50 };

	obj1 = new BoxCollider({ 650,60 }, { 10,10 }, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false);
	PhysicsComponent* obj2 = new CircleCollider({ 600,60 }, 20, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false);

	AddPhysicsObject(obj1);
	AddPhysicsObject(new BoxCollider({ 600,60 }, { 10,10 }, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false));
	AddPhysicsObject(obj2);
	AddPhysicsObject(new CircleCollider({ 600,60 }, 20, 0, b2BodyType::b2_dynamicBody));
	AddPhysicsObject(new CircleCollider({ 600,60 }, 20, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false));
	AddPhysicsObject(new CircleCollider({ 600,60 }, 20, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false));
	AddJoint(new RevoluteJoint(obj1->GetBody(), obj2->GetBody(),true,true));
	AddPhysicsObject(new PolygonCollider({ 600,60 }, 3,vertices, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false));
	AddPhysicsObject(new PolygonCollider({ 600,60 }, 3, vertices, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false));
	AddPhysicsObject(new PolygonCollider({ 600,60 }, 3, vertices, 0, b2BodyType::b2_dynamicBody, 1.0f, 1.0f, 0.05f, false));
	AddPhysicsObject(new BoxCollider({ 600,-1001 }, { 1800,10 }, 0, b2BodyType::b2_staticBody, 1.0f, 1.0f, 0.0f, false));
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


