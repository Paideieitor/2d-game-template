#ifndef REVOLUTEJOINT_H
#define REVOLUTEJOINT_H

#include "Joint.h"


class b2RevoluteJoint;
class b2Body;

class RevoluteJoint : public Joint
{
public:
	RevoluteJoint(b2Body* bodyA, b2Body* bodyB,bool enableLimit, bool collideConnected);
	~RevoluteJoint();

private:

	b2RevoluteJoint* joint;
};

#endif