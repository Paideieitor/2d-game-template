#include "Point.h"
#include <vector>
#include <memory> // for the shared pointer, erase when no texture
class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class b2Body;
class b2Fixture;
class Texture;
class b2PolygonShape;
enum  b2BodyType;
struct b2Vec2;

enum ColliderType
{
BOX_COLLIDER,
POLYGON_COLLIDER,
CIRCLE_COLLIDER,
NONE
};


class PhysicsComponent
{
public:

	PhysicsComponent(ColliderType type, b2BodyType bodyType, fpoint position, fpoint dimentions,float rotation, float density, float friction,float restitution,bool isSensor);
	~PhysicsComponent();
	b2Body* GetBody();

	fpoint GetPosition();
	fpoint GetLinearVelocity();
	float GetAngularVelocity();
	float GetRotation();


	void SetPosition(float x, float y);
	void SetLinearVelocity(float x, float y);
	void SetAngularVelocity(float velocity);
	void SetRotationAngle(float rotation);

	virtual void DebugDraw();

private:

	b2PolygonShape* GetVertex();
	void DrawRectangle();

	b2Body* body = nullptr;
	float rotationAngle;

	std::vector<b2Vec2> vertices;
	ColliderType colliderType = ColliderType::NONE;

	TexturePtr test;

	b2Fixture* fixture = nullptr;
};
