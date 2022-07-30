#include "Player.h"

#include "Textures.h"
#include "Render.h"
#include "Physics.h"
#include "Input.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "ContactListener.h"
#include "WeldJoint.h"


Player::Player(const std::string& name, const fpoint& position, float rotation)
    : Entity(Entity::Type::PLAYER, name, position, rotation)
{
	texture = game->textures->Load("images/AnimationTest.png");
	idle = MakeAnimation(true, 0.15f, 4u, ipoint(0, 0), ipoint(80, 100), 4u, 1u);
	current = idle;

	collider = new BoxCollider(position, {40,65},rotation, BodyType::DYNAMIC, 0.5f, 1, 0, true, false, "player");
	playerSensor = new BoxCollider(position, { 40,7 }, rotation, BodyType::DYNAMIC, 1.0f, 0.0f, 0.0f, true,true, "player_sensor");

	joint = new WeldJoint(collider->GetBody(), playerSensor->GetBody(), { 0,0 }, {0,40}, 0.0f, 5.0f, 0.0f,false);

	game->physics->AddJoint(joint);
	game->physics->AddJoint(jointTwo);
	game->physics->AddPhysicsObject(collider);
	game->physics->AddPhysicsObject(playerSensor);
}

Player::~Player()
{	
	game->physics->DestroyJoint(joint);
	game->physics->DestroyPhysicsObject(collider);
	game->physics->DestroyPhysicsObject(circleCollider);
}

bool Player::Update(float dt)
{
	ManageGroundedState();

	if (grounded && game->input->CheckState(Key::W) == Input::State::DOWN) 
	{
		collider->SetLinearVelocity(collider->GetLinearVelocity().x,jumpForce);
		canDoubleJump = true;
	}

	if (canDoubleJump && game->input->CheckState(Key::W) == Input::State::DOWN)
	{
		collider->SetLinearVelocity(collider->GetLinearVelocity().x, jumpForce);
		canDoubleJump = false;
	}
		
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

	if (playerSensor->inAir && collider->GetLinearVelocity().y < 0)
		collider->SetLinearVelocity(collider->GetLinearVelocity().x, collider->GetLinearVelocity().y);

	if(collider->GetLinearVelocity().y < -maxYvelocity)
		collider->SetLinearVelocity(collider->GetLinearVelocity().x, -maxYvelocity);

	if(collider->GetLinearVelocity().x > maxXvelocity)
		collider->SetLinearVelocity(maxXvelocity, collider->GetLinearVelocity().y);

	if (collider->GetLinearVelocity().x < -maxXvelocity)
		collider->SetLinearVelocity(-maxXvelocity, collider->GetLinearVelocity().y);

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

void Player::ManageGroundedState()
{
	if (playerSensor->contacts.size() > 0)
	{
		grounded = true;
		canDoubleJump = true;
	}
	else
	{
		grounded = false;
	}
}

float Player::lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}
