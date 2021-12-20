#include "Point.h"

class PhysicsComponent
{
public:

	PhysicsComponent();

	fpoint GetPosition();
	fpoint GetVelocity();
	fpoint GetAcceleration();
	float GetRotationAngle();

	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);
	void SetAcceleration(float x, float y);
	void SetRotationAngle(float rotation);

private:

	fpoint position;
	fpoint velocity;
	fpoint acceleration;
	float rotationAngle;

};
