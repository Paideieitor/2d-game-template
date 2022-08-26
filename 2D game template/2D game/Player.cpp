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
	texture = game->textures->Load("images/spritesheet.png");
	textureTest = game->textures->Load("images/spritesheet.png");

	idle = MakeAnimation(true, 0.15f, 4u, ipoint(0, 0), ipoint(80, 100), 4u, 1u);
	idleTest = MakeAnimation(true, 0.15f, 6u, ipoint(0, 0), ipoint(48, 49), 6u, 1u);
	current = idleTest;


	bodyCollider = new BoxCollider(position, {20,33},rotation, BodyType::DYNAMIC, 0.5f, 1, 0, true, false, "player");
	footSensor = new BoxCollider(position, { 20,4 }, rotation, BodyType::DYNAMIC, 1.0f, 0.0f, 0.0f, true,true, "player_sensor");

	crouchBodyCollider = new BoxCollider(position, { 40,30 }, rotation, BodyType::DYNAMIC, 0.5f, 1, 0, true, false, "player_crouch");

	joint = new WeldJoint(bodyCollider->GetBody(), footSensor->GetBody(), { 0,0 }, {0,20}, 0.0f, 5.0f, 0.0f,false);

	game->physics->AddJoint(joint);
	game->physics->AddPhysicsObject(bodyCollider);
	game->physics->AddPhysicsObject(footSensor);
}

Player::~Player()
{	
	game->physics->DestroyJoint(joint);
	game->physics->DestroyPhysicsObject(bodyCollider);
	game->physics->DestroyPhysicsObject(footSensor);
}

bool Player::Update(float dt)
{
	ManageGroundedState();

	bool playerMoved = false;

	if (grounded && game->input->CheckState(Key::W) == Input::State::DOWN) 
	{
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x,jumpForce);
		playerState = PlayerState::JUMPING;
		playerMoved = true;
	}

	
	if (game->input->CheckState(Key::A) == Input::State::REPEAT) 
	{
		currentVelocity -= dt * acceleration;
		if (currentVelocity < -velocity)
			currentVelocity = -velocity;
		playerState = PlayerState::WALKING;
		bodyCollider->SetLinearVelocity(currentVelocity, bodyCollider->GetLinearVelocity().y);
		playerMoved = true;
		Xinput = true;
	}

	if (game->input->CheckState(Key::D) == Input::State::REPEAT)
	{
		currentVelocity += dt * acceleration;
		if (currentVelocity > velocity)
			currentVelocity = velocity;
		playerState = PlayerState::WALKING;
		bodyCollider->SetLinearVelocity(currentVelocity, bodyCollider->GetLinearVelocity().y);
		playerMoved = true;
		Xinput = true;
	}

	if (game->input->CheckState(Key::C) == Input::State::DOWN)
	{
		if (playerState != PlayerState::CROUCHING)
		{
			playerState = PlayerState::CROUCHING;
			playerMoved = true;
		}
		else 
		{
			playerState = PlayerState::IDLE;
		}
		ManageCrouchStandState();
	}


	if (!playerMoved && playerState != PlayerState::CROUCHING) 
	{
		playerState = PlayerState::IDLE;
	}

	if (footSensor->inAir && bodyCollider->GetLinearVelocity().y < 0)
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x, bodyCollider->GetLinearVelocity().y);

	if(bodyCollider->GetLinearVelocity().y < -maxYvelocity)
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x, -maxYvelocity);

	if(bodyCollider->GetLinearVelocity().x > maxXvelocity)
		bodyCollider->SetLinearVelocity(maxXvelocity, bodyCollider->GetLinearVelocity().y);

	if (bodyCollider->GetLinearVelocity().x < -maxXvelocity)
		bodyCollider->SetLinearVelocity(-maxXvelocity, bodyCollider->GetLinearVelocity().y);

	if(playerState == PlayerState::IDLE)
		bodyCollider->SetLinearVelocity(0, bodyCollider->GetLinearVelocity().y);

	position = bodyCollider->GetPosition();
	rotation = bodyCollider->GetRotation();

	Frame frame = current->GetFrame();
	ipoint size = current->GetCurrentSize();

	game->render->RenderTexture(false, 5, texture, { position.x - frame.size.x * 0.5f ,position.y - frame.size.y * 0.5f  }, frame.position.x, frame.position.y, frame.size, false, 255, true);


	currentVelocity = bodyCollider->GetLinearVelocity().x;
	std::cout << "current: " << currentVelocity << "\n";
	/*
	switch (playerState) 
	{
	case PlayerState::IDLE:
		std::cout << "IDLE" << "\n";
		break;
	case PlayerState::WALKING:
		std::cout << "WALKING" << "\n";
		break;
	case PlayerState::JUMPING:
		std::cout << "JUMPING" << "\n";
		break;
	case PlayerState::CROUCHING:
		std::cout << "CROUCHING" << "\n";
		break;
	case PlayerState::DEATH:
		std::cout << "DEATH" << "\n";
		break;
	case PlayerState::CONTACT:
		std::cout << "CONTACT" << "\n";
		break;
	case PlayerState::SLOW_WALKING:
		std::cout << "SLOW_WALKING" << "\n";
		break;
	case PlayerState::IDLE_CROUCH:
		std::cout << "IDLE_CROUCH" << "\n";
		break;
	default:
		std::cout << "error" << "\n";
		break;
	}*/
	//std::cout << "X: " << position.x << "Y:" << position.y << "\n";

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
	if (footSensor->contacts.size() > 0)
	{
		grounded = true;
	}
	else
	{
		grounded = false;
	}
}

void Player::ManageCrouchStandState()
{
	if (playerState == PlayerState::CROUCHING) 
	{
		game->physics->DestroyJoint(joint);
		game->physics->DestroyPhysicsObject(bodyCollider);
		//game->physics->DestroyPhysicsObject(footSensor);

		crouchBodyCollider = new BoxCollider(position, { 40,30 }, rotation, BodyType::DYNAMIC, 0.5f, 1, 0, true, false, "player_crouch");
		//footSensor = new BoxCollider(position, { 40,7 }, rotation, BodyType::DYNAMIC, 1.0f, 0.0f, 0.0f, true, true, "player_sensor");

		joint = new WeldJoint(crouchBodyCollider->GetBody(), footSensor->GetBody(), { 0,0 }, { 0,40 }, 0.0f, 5.0f, 0.0f, false);

		game->physics->AddJoint(joint);
		game->physics->AddPhysicsObject(crouchBodyCollider);
		//game->physics->AddPhysicsObject(footSensor);
	}
	else if (playerState == PlayerState::IDLE) 
	{
		game->physics->DestroyJoint(joint);
		game->physics->DestroyPhysicsObject(crouchBodyCollider);
		//game->physics->DestroyPhysicsObject(footSensor);

		bodyCollider = new BoxCollider(position, { 40,65 }, rotation, BodyType::DYNAMIC, 0.5f, 1, 0, true, false, "player");
		//footSensor = new BoxCollider(position, { 40,7 }, rotation, BodyType::DYNAMIC, 1.0f, 0.0f, 0.0f, true, true, "player_sensor");

		joint = new WeldJoint(bodyCollider->GetBody(), footSensor->GetBody(), { 0,0 }, { 0,40 }, 0.0f, 5.0f, 0.0f, false);

		game->physics->AddJoint(joint);
		game->physics->AddPhysicsObject(bodyCollider);
		//game->physics->AddPhysicsObject(footSensor);
	}
}

float Player::lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}

