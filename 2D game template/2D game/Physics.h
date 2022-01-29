#include "Module.h"

struct b2Vec2;
class b2World;
class b2Body;
class PhysicsComponent;
class Joint;
class ContactListener;


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

	void AddJoint(Joint* joint);
	void DestroyJoint(Joint* joint);

	void PhysicsDebugDraw();

private:
	PhysicsComponent* obj1;
	ContactListener* listener;
	std::vector<PhysicsComponent*> physicsObjects;
	std::vector<Joint*> joints;

	b2World* world;
	float gravity = -205.0f;

};