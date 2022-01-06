#include "Player.h"

#include "Textures.h"
#include "Render.h"

#include "Physics.h"
#include "PhysicsComponent.h"
#include "BOX2D/Box2D/Box2D.h"

Player::Player(const std::string& name, const fpoint& position, float rotation)
    : Entity(Entity::Type::PLAYER, name, position, rotation)
{
	texture = game->textures->Load("images/AnimationTest.png");
	idle = MakeAnimation(true, 0.15f, 4u, ipoint(0, 0), ipoint(80, 100), 4u, 1u);
	current = idle;

	fpoint size = fpoint((float)current->GetCurrentSize().x * 0.5f, (float)current->GetCurrentSize().y * 0.5f);
	collider = new PhysicsComponent(ColliderType::BOX_COLLIDER, b2BodyType::b2_dynamicBody, position, size, rotation, 1.0f, 0.5f, 0.2f, false);
	game->physics->AddPhysicsObject(collider);
}

Player::~Player()
{
	game->physics->DestroyPhysicsObject(collider);
}

bool Player::Update(float dt)
{
	position = collider->GetPosition();
	rotation = collider->GetRotation();

	Frame frame = current->GetFrame();
	ipoint size = current->GetCurrentSize();
	game->render->RenderTexture(25, texture, GetRenderPosition(size), frame, false, 255, true, 1.0f, (double)GetRotation(), fpoint((float)size.x * 0.5f, (float)size.y * 0.5f));

    return true;
}

void Player::PositionChanged()
{
}

void Player::RotationChanged()
{
}
