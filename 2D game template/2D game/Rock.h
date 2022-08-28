#ifndef ROCK_H
#define ROCK_H

#include "Entity.h"

class PhysicsComponent;
class BoxCollider;

class Rock : public Entity
{
public:

	Rock(const std::string& name, const fpoint& position, const ipoint& size, float rotation);
	~Rock();

	bool Update(float dt);

	void PositionChanged() override;
	void RotationChanged() override;
private:

	TexturePtr texture;

	BoxCollider* rockCollider;

	friend class EntityManager;
};

#endif