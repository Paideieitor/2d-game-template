#include "Physics.h"
#include "PhysicsComponent.h"
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
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 400,3 }, { 60,23 },0,1.0f,0.3f,0.21f,false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 490,2 }, { 15,38 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 530,90 }, { 23,48 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 500,30}, { 18,30 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 510,0 }, { 23,48 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 400,3 }, { 40,23 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 490,2 }, { 15,38 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 530,90 }, { 28,44 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 500,30 }, { 15,30 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 510,0 }, { 23,44 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 400,3 }, { 40,23 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 490,2 }, { 15,38 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 530,90 }, { 23,44 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 500,30 }, { 85,30 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, { 510,0 }, { 23,44 }, 0, 1.0f, 0.3f, 0.21f, false));
	AddPhysicsObject(new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_staticBody, { 100,-600 }, { 1500,20 }, -20, 1.0f, 0.3f, 0.23f, false));
	return true;
}

bool Physics::Update(float dt)
{
	if (game->input->CheckState(Key::W) == Input::State::REPEAT)
		physicsObjects[0]->GetBody()->ApplyForce(b2Vec2((game->input->GetMousePos().x - physicsObjects[0]->GetBody()->GetPosition().x)*200, -(game->input->GetMousePos().y - physicsObjects[0]->GetBody()->GetPosition().y) * 100), physicsObjects[0]->GetBody()->GetWorldCenter(), true);
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
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		if(physicsObjects[i] == object)
		{
			world->DestroyBody(object->GetBody());
			delete physicsObjects[i];
		}
	}
}

void Physics::PhysicsDebugDraw()
{
	for(int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObjects[i]->DebugDraw();
	}
}


