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

private:

	TexturePtr texture;

	Animation current;
	Animation idle;

	PhysicsComponent* collider;
};

#endif
