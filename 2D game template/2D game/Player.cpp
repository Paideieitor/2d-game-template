#include "Player.h"

#include "Textures.h"
#include "Render.h"

#include "Physics.h"
#include "Input.h"
#include "PhysicsComponent.h"
#include "BoxCollider.h"

Player::Player(const std::string& name, const fpoint& position, float rotation)
    : Entity(Entity::Type::PLAYER, name, position, rotation)
{
	texture = game->textures->Load("images/sam.png");
	idle = MakeAnimation(true, 0.15f, 4u, ipoint(0, 0), ipoint(80, 100), 4u, 1u);
	current = idle;

	fpoint size = fpoint((float)current->GetCurrentSize().x * 0.5f, (float)current->GetCurrentSize().y * 0.5f);
	collider = new BoxCollider(position, {25,40},rotation, BodyType::DYNAMIC, 3.0f, 1, 0, true, false);
	game->physics->AddPhysicsObject(collider);
}

Player::~Player()
{
	game->physics->DestroyPhysicsObject(collider);
}

bool Player::Update(float dt)
{

	if (game->input->CheckState(Key::W) == Input::State::DOWN)
		collider->ApplyLinearImpulse({ 0,jumpForce }, true);

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
	//game->render->RenderTexture(25, texture, GetRenderPosition(size), frame, false, 255, true, 1.0f, -(double)GetRotation(), fpoint((float)size.x * 0.5f, (float)size.y * 0.5f));
	game->render->RenderTexture(5, texture, { position.x - texture->GetSize().x*2 ,position.y - texture->GetSize().y*2  }, 0, 0, texture->GetSize() * 4, false, 255, false);

    return true;
}

void Player::PositionChanged()
{
}

void Player::RotationChanged()
{
}
