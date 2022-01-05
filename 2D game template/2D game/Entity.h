#ifndef ENTITY_H
#define ENTITY_H

#include "Point.h"

#include <string>

class Entity
{
public:

	enum class Type
	{
		ENTITY,
		PLAYER
	};

	Entity() = delete;
	Entity(Entity::Type type, const std::string& name, const fpoint& position, double rotation);
	virtual ~Entity();

	virtual bool Update(float dt) = 0;

	const fpoint GetPosition() const { return position; }
	void SetPosition(const fpoint& position);

	const double GetRotation() const { return rotation; }
	void SetRotation(double rotation);

public:

	const Entity::Type type;
	const std::string name;

protected:

	virtual void PositionChanged() = 0;
	virtual void RotationChanged() = 0;

private:

	fpoint position;
	double rotation;
};

#endif
