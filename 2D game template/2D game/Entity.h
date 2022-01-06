#ifndef ENTITY_H
#define ENTITY_H

#include "Game.h"

#include "Animation.h"

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class Entity
{
public:

	enum class Type
	{
		ENTITY,
		PLAYER
	};

	Entity() = delete;
	Entity(Entity::Type type, const std::string& name, const fpoint& position, float rotation);
	virtual ~Entity();

	virtual bool Update(float dt) = 0;

	const fpoint GetPosition() const { return position; }
	void SetPosition(const fpoint& position);

	const float GetRotation() const { return rotation; }
	void SetRotation(float rotation);

public:

	const Entity::Type type;
	const std::string name;

protected:

	virtual void PositionChanged() = 0;
	virtual void RotationChanged() = 0;

	fpoint GetRenderPosition(ipoint size);

protected:

	fpoint position;
	float rotation;
};

#endif
