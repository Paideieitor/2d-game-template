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

	idle = MakeAnimation(true, 0.15f, 4u, ipoint(0, 0), ipoint(80, 100), 4u, 1u);
	idleTest = MakeAnimation(true, 0.15f, 6u, ipoint(0, 0), ipoint(48, 49), 6u, 1u);
	current = idleTest;


	bodyCollider = new BoxCollider(position, {20,33},rotation, BodyType::DYNAMIC, 0.5f, 0, 0, true, false, "player");
	footSensor = new BoxCollider(position, { 18,2 }, rotation, BodyType::DYNAMIC, 1.0f, 0.0f, 0.0f, true,true, "player_sensor");
	grabSensor = new BoxCollider(position, { 30, 20 }, rotation, BodyType::DYNAMIC, 0.0f,0.0f, 0.0f,true,true, "grab_sensor");

	footJoint = new WeldJoint(bodyCollider->GetBody(), footSensor->GetBody(), { 0,0 }, {0,17}, 0.0f, 5.0f, 0.0f,false);
	grabJoint = new WeldJoint(bodyCollider->GetBody(), grabSensor->GetBody(), { 0,0 }, { 0,0 }, 0.0f, 5.0f, 0.0f, false);

	game->physics->AddJoint(footJoint);
	game->physics->AddPhysicsObject(bodyCollider);
	game->physics->AddPhysicsObject(footSensor);
	game->physics->AddPhysicsObject(grabSensor);
	game->physics->AddJoint(grabJoint);
}

Player::~Player()
{	
	game->physics->DestroyJoint(footJoint);
	game->physics->DestroyJoint(grabJoint);
	game->physics->DestroyPhysicsObject(bodyCollider);	
	game->physics->DestroyPhysicsObject(footSensor);
	game->physics->DestroyPhysicsObject(grabSensor);

}

bool Player::Update(float dt)
{
	//CHECK GOUNDED STATE
	ManageGroundedState();
	ManagerGrabingBlock();
	ManageAirJumpThreshold(dt);
	bool playerMoved = false;

	//JUMPING
	if (grounded && (game->input->CheckState(Key::W) == Input::State::DOWN || game->input->CheckState(Key::SPACE) == Input::State::DOWN))
	{
		if (playerState == PlayerState::IDLE_CROUCH || playerState == PlayerState::CROUCH_WALK) 
		{
			playerState = PlayerState::IDLE;
			crouching = false;
			ManageCrouchStandState();
		}	

		if (objectGrabbed) 
			DetachGrabJoint();
		
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x,jumpForce);

		playerState = PlayerState::JUMPING;
		playerMoved = true;
	}

	//CHECK JUMP IN AIR
	if (!grounded && (game->input->CheckState(Key::W) == Input::State::DOWN || game->input->CheckState(Key::SPACE) == Input::State::DOWN))
		jumpThresholdCounter = jumpThreshold;

	//MOVEMENT
	if (game->input->CheckState(Key::A) == Input::State::REPEAT) 
	{
		currentVelocity -= dt * acceleration;
		if (currentVelocity < -velocity)
			currentVelocity = -velocity;

		if(!crouching)
		{
			playerState = PlayerState::WALKING;
			bodyCollider->SetLinearVelocity(currentVelocity, bodyCollider->GetLinearVelocity().y);
		}
		else 
		{	
			playerState = PlayerState::CROUCH_WALK;
			bodyCollider->SetLinearVelocity(currentVelocity/crouchVel, bodyCollider->GetLinearVelocity().y);
		}
		

		playerMoved = true;
		left = true;
	}

	if (game->input->CheckState(Key::D) == Input::State::REPEAT)
	{
		currentVelocity += dt * acceleration;
		if (currentVelocity > velocity)
			currentVelocity = velocity;

		if (!crouching) 
		{
			playerState = PlayerState::WALKING;
			bodyCollider->SetLinearVelocity(currentVelocity, bodyCollider->GetLinearVelocity().y);
		}
		else 
		{
			playerState = PlayerState::CROUCH_WALK;
			bodyCollider->SetLinearVelocity(currentVelocity/crouchVel, bodyCollider->GetLinearVelocity().y);
		}

		playerMoved = true;
		left = false;
	}


	//CROUCH
	if ((game->input->CheckState(Key::C) == Input::State::DOWN || game->input->CheckState(Key::LCTRL) == Input::State::DOWN) && grounded)
	{
		if (playerState != PlayerState::IDLE_CROUCH && playerState != PlayerState::CROUCH_WALK)
		{
			playerState = PlayerState::IDLE_CROUCH;
			crouching = true;
			playerMoved = true;
		}
		else 
		{
			playerState = PlayerState::IDLE;
			crouching = false;
		}
		ManageCrouchStandState();
	}

	//SET STATE TO IDLE IF NO MOVEMENT DETECTED
	if (!playerMoved && playerState != PlayerState::CROUCHING) 
	{
		if (!grounded)
		{
			float yVelocity = bodyCollider->GetLinearVelocity().y;
			if (yVelocity > 100)
				playerState = PlayerState::JUMPING;
			else if (yVelocity < 100 && yVelocity > 0)
				playerState = PlayerState::TOP_REACHING;
			else
				playerState = PlayerState::FALLING;
		}
		else if(crouching)
			playerState = PlayerState::IDLE_CROUCH;
		else if(objectGrabbed)
			playerState = PlayerState::IDLE_GRABBING;
		else
			playerState = PlayerState::IDLE;
	}

	//VINE MOVEMENT
	if (bodyCollider->inVine)
	{
		ManageVineMovement();
	}
		

	//VELOCITY CHECKERS
	if(bodyCollider->GetLinearVelocity().y < -maxYvelocity)
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x, -maxYvelocity);

	if(bodyCollider->GetLinearVelocity().x > maxXvelocity)
		bodyCollider->SetLinearVelocity(maxXvelocity, bodyCollider->GetLinearVelocity().y);

	if (bodyCollider->GetLinearVelocity().x < -maxXvelocity)
		bodyCollider->SetLinearVelocity(-maxXvelocity, bodyCollider->GetLinearVelocity().y);

	if (playerState == PlayerState::IDLE || playerState == PlayerState::IDLE_CROUCH || playerState == PlayerState::FALLING || playerState == PlayerState::IDLE_GRABBING)
	{
		if(bodyCollider->GetLinearVelocity().x > 0.0f)
			bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x - deceleration *dt, bodyCollider->GetLinearVelocity().y);
		else if (bodyCollider->GetLinearVelocity().x < 0.0f)
			bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x + deceleration *dt, bodyCollider->GetLinearVelocity().y);
		
		if(bodyCollider->GetLinearVelocity().x < 40.0f && bodyCollider->GetLinearVelocity().x > -40.0f)
			bodyCollider->SetLinearVelocity(0, bodyCollider->GetLinearVelocity().y);

	}


	//RENDERING
	position = bodyCollider->GetPosition();
	rotation = bodyCollider->GetRotation();

	Frame frame = current->GetFrame();
	ipoint size = current->GetCurrentSize();
	currentVelocity = bodyCollider->GetLinearVelocity().x;

	game->render->RenderTexture(false, 5, texture, { position.x - frame.size.x * 0.5f ,position.y - frame.size.y * 0.5f  }, frame.position.x, frame.position.y, frame.size, left, 255, true);

	LogState();

	if (grabSensor->inVine)
		end = true;

    return true;
}

void Player::PositionChanged()
{
}

void Player::RotationChanged()
{
}

void Player::LogState()
{
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
	case PlayerState::CROUCH_WALK:
		std::cout << "CROUCH_WALK" << "\n";
		break;
	case PlayerState::IDLE_CROUCH:
		std::cout << "IDLE_CROUCH" << "\n";
		break;
	case PlayerState::CONTACT_VINE:
		std::cout << "CONTACT_VINE" << "\n";
		break;
	case PlayerState::IDLE_GRABBING:
		std::cout << "GRABBING" << "\n";
		break;
	case PlayerState::GRABBING_WALK:
		std::cout << "GRABBING_WALK" << "\n";
		break;
	case PlayerState::FALLING:
		std::cout << "FALLING" << "\n";
		break;
	case PlayerState::TOP_REACHING:
		std::cout << "TOP_REACHING" << "\n";
		break; 
	case PlayerState::VINE_MOVEMENT:
		std::cout << "VINE_MOVEMENT" << "\n";
		break;
	default:
		std::cout << "error" << "\n";
		break;
	}
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
		DetachGrabJoint();
	}
}

void Player::ManageCrouchStandState()
{
	if (playerState == PlayerState::IDLE_CROUCH)
	{
		bodyCollider->ChangeFixture({20,15},0.5f, 1, 0, false);
	}
	else if (playerState == PlayerState::IDLE) 
	{
		bodyCollider->ChangeFixture({ 20,33 }, 0.5f, 1, 0, false);
	}
}

void Player::ManageAirJumpThreshold(float dt)
{
	jumpThresholdCounter -= dt;
	if(grounded && jumpThresholdCounter > 0.0f)
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x, jumpForce);
}

void Player::ManageVineMovement()
{
	playerState = PlayerState::CONTACT_VINE;
	bodyCollider->SetLinearVelocity(0, 0);

	if (game->input->CheckState(Key::A) == Input::State::REPEAT)
	{
		bodyCollider->SetLinearVelocity(-vineVelocity, bodyCollider->GetLinearVelocity().y);
		playerState = PlayerState::VINE_MOVEMENT;
	}

	if (game->input->CheckState(Key::D) == Input::State::REPEAT)
	{
		bodyCollider->SetLinearVelocity(vineVelocity, bodyCollider->GetLinearVelocity().y);
		playerState = PlayerState::VINE_MOVEMENT;
	}

	if (game->input->CheckState(Key::W) == Input::State::REPEAT)
	{
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x, vineVelocity);
		playerState = PlayerState::VINE_MOVEMENT;
	}

	if (game->input->CheckState(Key::S) == Input::State::REPEAT)
	{
		bodyCollider->SetLinearVelocity(bodyCollider->GetLinearVelocity().x, -vineVelocity);
		playerState = PlayerState::VINE_MOVEMENT;
	}
}

void Player::ManagerGrabingBlock()
{
	if(objectGrabbed && game->input->CheckState(Key::E) == Input::State::DOWN)
	{
		DetachGrabJoint();
	}

	if(grabSensor->contacts.size() && game->input->CheckState(Key::E) == Input::State::DOWN)
	{
		ipoint boxPos = grabSensor->contacts[0]->GetPosition();
		ipoint playerPos = bodyCollider->GetPosition();
		ipoint jointPos = boxPos - playerPos;
		grabberJoint = new WeldJoint(grabSensor->contacts[0]->GetBody(), grabSensor->GetBody(), jointPos, { 0,0 }, 0.0f, 5.0f, 0.0f, false);
		game->physics->AddJoint(grabberJoint);
		objectGrabbed = true;
	}
}

void Player::DetachGrabJoint()
{
	objectGrabbed = false;
	game->physics->DestroyJoint(grabberJoint);
}

float Player::lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}

