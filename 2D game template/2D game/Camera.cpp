#include "Camera.h"

#include "Render.h"

Camera::Camera(const fpoint& position) : Entity(Entity::Type::CAMERA, "Camera", position, 0)
{
}

Camera::~Camera()
{
}

bool Camera::Update(float dt)
{
	switch (mode)
	{
	case Camera::Mode::IDLE:
		break;
	case Camera::Mode::FOLLOW_ENTITY:
		destination = follow->GetPosition(); // break intentionally missing
	case Camera::Mode::MOVE:
		Lerp();
		break;
	}

	return true;
}

void Camera::PositionChanged()
{
	game->render->SetCameraPosition((ipoint)(GetPosition() - (fpoint)game->render->GetResolution(false) * 0.5f) * -1);
}

void Camera::RotationChanged()
{
}

void Camera::Lerp()
{
	fpoint position = GetPosition();

	float distance = abs(position.DistanceNoSqrt(destination));
	if (distance <= stopdistance)
	{
		if (mode == Mode::MOVE)
			mode = Mode::IDLE;
		return;
	}

	fpoint direction = (destination - position).Normalize();

	float currentspeed = speed;
	if (acceleration)
		currentspeed = speed + speed * distance * 0.001f;

	SetPosition(position + direction * currentspeed);
}

void Camera::Follow(Entity* entity, float speed, float stopdistance, bool acceleration)
{
	if (!entity)
		return;

	mode = Mode::FOLLOW_ENTITY;

	follow = entity;
	this->speed = speed;
	this->stopdistance = stopdistance * stopdistance; // to use distance with no square root
	this->acceleration = acceleration;
}

void Camera::Move(fpoint position, float speed, float stopdistance, bool acceleration)
{
	mode = Mode::MOVE;

	if (follow)
		follow = nullptr;

	destination = position;
	this->speed = speed;
	this->stopdistance = stopdistance * stopdistance; // to use distance with no square root
	this->acceleration = acceleration;
}

void Camera::Stop()
{
	mode = Mode::IDLE;

	if (follow)
		follow = nullptr;
}
