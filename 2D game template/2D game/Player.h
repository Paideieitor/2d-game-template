#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class PhysicsComponent;

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
	float jumpForce = 400;
	bool playerIsMoving;

	TexturePtr texture;

	Animation current;
	Animation idle;

	PhysicsComponent* collider;

	friend class EntityManager;
};

#endif
