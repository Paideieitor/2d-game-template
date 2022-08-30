#include "Vine.h"
#include "Textures.h"
#include "Render.h"
#include "Physics.h"
#include "Input.h"

#include "BoxCollider.h"

Vine::Vine(const std::string& name, const fpoint& position, const ipoint& size) : Entity(Entity::Type::ENTITY, name, position, rotation)
{
	texture = game->textures->Load("images/vine.png");

	vineCollider = new BoxCollider(position, size, rotation, BodyType::STATIC, 0.5f, 1, 0, false, true, "vine");

	game->physics->AddPhysicsObject(vineCollider);
}

Vine::~Vine()
{
	game->physics->DestroyPhysicsObject(vineCollider);
}

bool Vine::Update(float dt)
{
	position = vineCollider->GetPosition();

	game->render->RenderTexture(false, 5, texture, { position.x - texture->GetSize().x * 0.5f , position.y - texture->GetSize().y * 0.5f }, 0, 0, texture->GetSize());

	return true;
}

void Vine::PositionChanged()
{
}

void Vine::RotationChanged()
{
}
