#include "Player.h"

#include "Textures.h"
#include "Render.h"
#include "Physics.h"
#include "Input.h"

#include "BoxCollider.h"

#include <cmath>

Player::Player(const std::string& name, const fpoint& position, float rotation)
    : Entity(Entity::Type::PLAYER, name, position, rotation)
{
	texture = game->textures->Load("images/AnimationTest.png");
	idle = MakeAnimation(true, 0.15f, 4u, ipoint(0, 0), ipoint(80, 100), 4u, 1u);
	current = idle;

	collider = new BoxCollider(position, {60,80},rotation, BodyType::DYNAMIC, 3.0f, 1, 0, true, false);
	game->physics->AddPhysicsObject(collider);
}

Player::~Player()
{
	game->physics->DestroyPhysicsObject(collider);
}

bool Player::Update(float dt)
{

	if (game->input->CheckState(Key::W) == Input::State::DOWN)
		collider->SetLinearVelocity(collider->GetLinearVelocity().x,jumpForce);

	playerIsMoving = false;

	if (game->input->CheckState(Key::A) == Input::State::REPEAT) 
	{
		playerIsMoving = true;
		collider->SetLinearVelocity(-velocity, collider->GetLinearVelocity().y);
	}


	if (game->input->CheckState(Key::D) == Input::State::REPEAT)
	{
		playerIsMoving = true;
		collider->SetLinearVelocity(velocity, collider->GetLinearVelocity().y);
	}

		
	if(!playerIsMoving)
		collider->SetLinearVelocity(0, collider->GetLinearVelocity().y);

	position = collider->GetPosition();
	rotation = collider->GetRotation();

	Frame frame = current->GetFrame();
	ipoint size = current->GetCurrentSize();

	game->render->RenderTexture(false, 5, texture, { position.x - frame.size.x * 0.5f ,position.y - frame.size.y * 0.5f  }, frame.position.x, frame.position.y, frame.size, false, 255, true);

    return true;
}

void Player::PositionChanged()
{
}

void Player::RotationChanged()
{
}
