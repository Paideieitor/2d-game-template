#include "Entity.h"

#include "EntityManager.h"

Entity::Entity(Entity::Type type, const std::string& name, const fpoint& position, float rotation)
	: type(type), name(name), position(position), rotation(rotation)
{
	game->entities->AddEntity(this);
}

Entity::~Entity()
{
	game->entities->EraseEntity(this);
}

void Entity::SetPosition(const fpoint& position)
{
	this->position = position;

	PositionChanged();
}

void Entity::SetRotation(float rotation)
{
	this->rotation = rotation;

	RotationChanged();
}

fpoint Entity::GetRenderPosition(ipoint size)
{
	return fpoint(position.x - (float)size.x * 0.5f, position.y - (float)size.y * 0.5f);
}
