#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class PhysicsComponent;
class Joint;
class BoxCollider;

enum PlayerState 
{
	IDLE,
	WALKING,
	SLOW_WALKING,
	DEATH,

	// AIR
	JUMPING,
	FALLING,
	CONTACT,

	//CROUCH
	CROUCHING,
	IDLE_CROUCH,
	CROUCH_WALK,

	CONTACT_VINE
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

	void LogState();
	void ManageGroundedState();
	void ManageCrouchStandState();

	float lerp(float a, float b, float f);

	PlayerState playerState = PlayerState::IDLE;

	float velocity = 150;
	float jumpForce = 490;
	float currentVelocity = 0.0f;
	float maxYvelocity = 700;
	float maxXvelocity = 280;


	float acceleration = 950;
	float deceleration = 500;

	bool jumping = false;
	bool Xinput = false;
	bool crouching = false;

	TexturePtr texture;

	Animation current;
	Animation idle;
	Animation idleTest;

	BoxCollider* bodyCollider;

	PhysicsComponent* footSensor;

	Joint* joint;

	bool grounded = false;
	friend class EntityManager;
};

#endif
