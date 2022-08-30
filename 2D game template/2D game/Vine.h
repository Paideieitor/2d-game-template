#ifndef VINE_H
#define VINE_H

#include "Entity.h"

class PhysicsComponent;
class BoxCollider;

class Vine : public Entity
{
public:

	Vine(const std::string& name, const fpoint& position, const ipoint& size);
	~Vine();

	bool Update(float dt);

	void PositionChanged() override;
	void RotationChanged() override;
private:

	TexturePtr texture;

	BoxCollider* vineCollider;

	friend class EntityManager;
};

#endif