#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"

class Camera : public Entity
{
private:

	enum class Mode
	{
		IDLE,
		FOLLOW_ENTITY,
		MOVE
	};

private:

	Camera() = delete;
	Camera(const fpoint& position);
	~Camera();

	bool Update(float dt);

	void PositionChanged() override;
	void RotationChanged() override;

	void Lerp();

public:

	void Follow(Entity* entity, float speed, float stopdistance);
	void Move(fpoint position, float speed, float stopdistance);

	void Stop();

private:

	Mode mode = Mode::IDLE;

	Entity* follow = nullptr;

	fpoint destination = fpoint();

	float speed = 0.0f;
	float stopdistance = 0.0f;

	friend class EntityManager;
};

#endif

