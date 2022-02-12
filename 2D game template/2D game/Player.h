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

	float velocity = 500;
	float jumpForce = 450;
	bool playerIsMoving;
	bool jumping = false;

	TexturePtr texture;

	Animation current;
	Animation idle;

	PhysicsComponent* collider;
	PhysicsComponent* circleCollider;
	PhysicsComponent* playerSensor;

	Joint* joint;
	Joint* jointTwo;


	friend class EntityManager;
};

#endif
