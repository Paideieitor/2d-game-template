#ifndef WELDJOINT_H
#define WELDJOINT_H

#include "Joint.h"


class b2WeldJoint;
class b2Body;

class WeldJoint : public Joint
{
public:
	WeldJoint(b2Body* bodyA, b2Body* bodyB, ipoint localAnchorA, ipoint localAnchorB, float referenceAngle, float dampingRatio, float frequency, bool collideConnected);
	~WeldJoint();

private:

	b2WeldJoint* joint;
};

#endif