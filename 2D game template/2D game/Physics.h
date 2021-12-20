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

	b2World* world;
	b2Body* groundBody;
	PhysicsComponent* box;
	PhysicsComponent* box1;
	PhysicsComponent* box2;

private:

	b2Vec2* gravity;

};