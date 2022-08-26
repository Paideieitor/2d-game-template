#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class PhysicsComponent;
class Joint;

enum PlayerState 
{
	IDLE,
	WALKING,
	SLOW_WALKING,
	CROUCHING,
	IDLE_CROUCH,
	DEATH,

	// AIR
	JUMPING,
	FALLING,
	CONTACT
};


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
	void ManageCrouchStandState();

	float lerp(float a, float b, float f);

	PlayerState playerState = PlayerState::IDLE;

	float velocity = 150;
	float jumpForce = 400;
	float currentVelocity = 0.0f;
	float maxYvelocity = 700;
	float maxXvelocity = 280;


	float acceleration = 950;
	float deceleration = 500;

	bool jumping = false;
	bool Xinput = false;

	TexturePtr texture;
	TexturePtr textureTest;

	Animation current;
	Animation idle;
	Animation idleTest;

	PhysicsComponent* bodyCollider;
	PhysicsComponent* crouchBodyCollider;

	PhysicsComponent* footSensor;

	Joint* joint;
	Joint* jointTwo;

	bool grounded = false;
	friend class EntityManager;
};

#endif
