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

	if (abs(position.DistanceNoSqrt(destination)) <= stopdistance)
	{
		if (mode == Mode::MOVE)
			mode = Mode::IDLE;
		return;
	}

	
	fpoint direction = (destination - position).Normalize();

	SetPosition(position + direction * speed);
}

void Camera::Follow(Entity* entity, float speed, float stopdistance)
{
	if (!entity)
		return;

	mode = Mode::FOLLOW_ENTITY;

	follow = entity;
	this->speed = speed;
	this->stopdistance = stopdistance * stopdistance; // to use distance with no square root
}

void Camera::Move(fpoint position, float speed, float stopdistance)
{
	mode = Mode::MOVE;

	if (follow)
		follow = nullptr;

	destination = position;
	this->speed = speed;
	this->stopdistance = stopdistance * stopdistance; // to use distance with no square root
}

void Camera::Stop()
{
	mode = Mode::IDLE;

	if (follow)
		follow = nullptr;
}
