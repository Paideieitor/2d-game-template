#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class PhysicsComponent;
class Joint;

class Player : public Entity
{
private:

	Player() = delete;
	Player(const std::string& name, const fpoint& position, float rotation);
	~Player();

	bool Update(float dt);

	void PositionChanged() override;
	void RotationChanged() override;

private:

	void ManageGroundedState();

	float lerp(float a, float b, float f);

	float velocity = 230;
	float jumpForce = 400;
	float maxYvelocity = 700;
	float maxXvelocity = 280;
	float acceleration = 5;

	bool playerIsMoving;
	bool jumping = false;
	bool canDoubleJump = false;

	TexturePtr texture;

	Animation current;
	Animation idle;

	PhysicsComponent* collider;
	PhysicsComponent* circleCollider;
	PhysicsComponent* playerSensor;

	Joint* joint;
	Joint* jointTwo;

	bool grounded = false;
	friend class EntityManager;
};

#endif
