#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class PhysicsComponent;

class Player : public Entity
{
public:

	Player() = delete;
	Player(const std::string& name, const fpoint& position, float rotation);
	~Player();

	bool Update(float dt);

private:

	void PositionChanged();
	void RotationChanged();
	float Lerp(float a, float b, float f);

private:

	float velocity = 500;
	//craaaaaazy number
	float jumpForce = 400;
	bool playerIsMoving;

	TexturePtr texture;

	Animation current;
	Animation idle;

	PhysicsComponent* collider;
};

#endif
