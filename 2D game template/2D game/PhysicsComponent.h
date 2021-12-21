#include "Point.h"

class b2Body;
class b2Fixture;
class Texture;
enum  b2BodyType;

enum ColliderType
{
BOX_COLLIDER,
CIRCLE_COLLIDER,
NONE
};

class PhysicsComponent
{
public:

	PhysicsComponent(ColliderType type, b2BodyType bodyType, fpoint position, fpoint dimentions);
	~PhysicsComponent();
	fpoint GetDimentions();
	b2Body* GetBody();

	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);
	void SetAcceleration(float x, float y);
	void SetDimentions(float x, float y);
	void SetRotationAngle(float rotation);

	void DebugDraw();

private:

	b2Body* body = nullptr;
	fpoint position;
	fpoint velocity;
	fpoint dimentions;
	fpoint acceleration;
	float rotationAngle;
	ColliderType colliderType = ColliderType::NONE;


	b2Fixture* fixture = nullptr;


	Texture* debugTexture;
};
