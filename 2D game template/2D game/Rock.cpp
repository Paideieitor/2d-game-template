#include "Rock.h"

#include "Textures.h"
#include "Render.h"
#include "Physics.h"
#include "Input.h"

#include "BoxCollider.h"


Rock::Rock(const std::string& name, const fpoint& position, const ipoint& size, float rotation) : Entity(Entity::Type::ENTITY, name, position, rotation)
{
	texture = game->textures->Load("images/rock2.png");

	rockCollider = new BoxCollider(position, size, rotation, BodyType::DYNAMIC, 0.5f, 1, 0, false, false, "rock");

	game->physics->AddPhysicsObject(rockCollider);
}

Rock::~Rock()
{
	game->physics->DestroyPhysicsObject(rockCollider);
}

bool Rock::Update(float dt)
{
	position = rockCollider->GetPosition();
	rotation = rockCollider->GetRotation();

	game->render->RenderTexture(false, 5, texture, { position.x - texture->GetSize().x * 0.5f , position.y - texture->GetSize().y * 0.5f }, 0, 0, texture->GetSize(), false, 255, true, 1.0f, -rotation);

	return true;
}

void Rock::PositionChanged()
{
}

void Rock::RotationChanged()
{
}
