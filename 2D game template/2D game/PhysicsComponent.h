#include "Point.h"

#include <memory> // for the shared pointer, erase when no texture
class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class b2Body;
class b2Fixture;
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

	PhysicsComponent(ColliderType type, b2BodyType bodyType, fpoint position, fpoint dimentions,float rotation, float density, float friction,float restitution,bool isSensor);
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

	void DrawRectangle();
	b2Body* body = nullptr;
	fpoint position;
	fpoint velocity;
	fpoint dimentions;
	fpoint acceleration;
	float rotationAngle;
	ColliderType colliderType = ColliderType::NONE;

	TexturePtr test;

	b2Fixture* fixture = nullptr;
};
