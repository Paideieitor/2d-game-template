#include "Player.h"

#include "Textures.h"
#include "Render.h"
#include "Physics.h"
#include "Input.h"

#include "BoxCollider.h"

#include <cmath>
#include <cassert>
#include <iostream>

Player::Player(const std::string& name, const fpoint& position, float rotation)
    : Entity(Entity::Type::PLAYER, name, position, rotation)
{
	texture = game->textures->Load("images/sam.png");
	idle = MakeAnimation(true, 0.15f, 4u, ipoint(0, 0), ipoint(80, 100), 4u, 1u);
	current = idle;

	fpoint size = fpoint((float)current->GetCurrentSize().x * 0.5f, (float)current->GetCurrentSize().y * 0.5f);
	collider = new BoxCollider(position, {25,60},rotation, BodyType::DYNAMIC, 3.0f, 1, 0, true, false);
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


	float playerPosition = (float)(-(int)position.x + game->render->GetResolution(false).x / 2);
	float cameraPosition = (float)game->render->GetCameraPosition().x;

	float k = Lerp(playerPosition, cameraPosition, 1.0f);

	game->render->SetCameraPosition({(int)k,0/*-(int)position.y + game->render->GetResolution().y/2*/});
	


	
	
	
	Frame frame = current->GetFrame();
	ipoint size = current->GetCurrentSize();

	game->render->RenderTexture(false, 5, texture, { position.x - texture->GetSize().x*2 ,position.y - texture->GetSize().y*2  }, 0, 0, texture->GetSize() * 4, false, 255, true);

    return true;
}

void Player::PositionChanged()
{
}

void Player::RotationChanged()
{
}

float Player::Lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
