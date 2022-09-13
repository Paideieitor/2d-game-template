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
	TOP_REACHING,
	CONTACT,

	//CROUCH
	CROUCHING,
	IDLE_CROUCH,
	CROUCH_WALK,

	//VINE
	CONTACT_VINE,
	VINE_MOVEMENT,

	//GRAB
	IDLE_GRABBING,
	GRABBING_WALK,
};


class Player : public Entity
{
public:

	Player() = delete;
	Player(const std::string& name, const fpoint& position, float rotation);
	~Player();

	bool Update(float dt);

	void PositionChanged() override;
	void RotationChanged() override;
	bool end = false;
private:

	void LogState();
	void ManageGroundedState();
	void ManageCrouchStandState();
	void ManageVineMovement();
	void ManagerGrabingBlock();

	void DetachGrabJoint();

	float lerp(float a, float b, float f);

	PlayerState playerState = PlayerState::IDLE;

	float velocity = 150;
	float crouchVel = 1.2;
	float vineVelocity = 100;
	float jumpForce = 340;
	float currentVelocity = 0.0f;
	float maxYvelocity = 700;
	float maxXvelocity = 280;


	float acceleration = 950;
	float deceleration = 1.2;

	bool jumping = false;
	bool crouching = false;
	bool objectGrabbed = false;



	TexturePtr texture;

	Animation current;
	Animation idle;
	Animation idleTest;

	BoxCollider* bodyCollider;
	BoxCollider* grabSensor;
	PhysicsComponent* footSensor;

	Joint* footJoint;
	Joint* grabJoint;
	Joint* grabberJoint;

	bool grounded = false;
	bool left = false;
	friend class EntityManager;
};

#endif
