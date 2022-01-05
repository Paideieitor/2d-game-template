#include "Entity.h"

Entity::Entity(Entity::Type type, const std::string& name, const fpoint& position, double rotation) 
	: type(type), name(name), position(position), rotation(rotation)
{
}

Entity::~Entity()
{
}

void Entity::SetPosition(const fpoint& position)
{
	this->position = position;

	PositionChanged();
}

void Entity::SetRotation(double rotation)
{
	this->rotation = rotation;

	RotationChanged();
}
