#include "Module.h"

struct b2Vec2;
class b2World;
class b2Body;
class PhysicsComponent;

class Physics : public Module
{
public:
	Physics();
	~Physics();

	bool SetUp(pugi::xml_node&);
	bool Update(float dt);
	bool CleanUp();
	b2World* GetWorld();

	void CreateWorld(b2Vec2* gravity);

	void AddPhysicsObject(PhysicsComponent* object);
	void DestroyPhysicsObject(PhysicsComponent* object);
	void PhysicsDebugDraw();

	b2Body* groundBody;
	PhysicsComponent* box;
	PhysicsComponent* box1;
	PhysicsComponent* box2;
	PhysicsComponent* ground;



private:
	std::vector<PhysicsComponent*> physicsObjects;
	b2World* world;
	float gravity = -9.8f;

};