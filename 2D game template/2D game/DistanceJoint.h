#ifndef DISTANCEJOINT_H
#define DISTANCEJOINT_H

#include "Joint.h"


class b2DistanceJoint;
class b2Body;

class DistanceJoint : public Joint
{
public:
	DistanceJoint(b2Body* bodyA, b2Body* bodyB, float lenght);
	~DistanceJoint();

private:

	b2DistanceJoint* joint;
};

#endif