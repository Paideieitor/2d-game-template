#include "DistanceJoint.h"
#include "Physics.h"
#include "Game.h"
#include "BOX2D/Box2D/Box2D.h"

DistanceJoint::DistanceJoint(b2Body* bodyA, b2Body* bodyB, float lenght)
{
	b2DistanceJointDef jointDef;
	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;
	jointDef.length = lenght;
	jointDef.collideConnected = true;

	joint = (b2DistanceJoint*)game->physics->GetWorld()->CreateJoint(&jointDef);
}

DistanceJoint::~DistanceJoint()
{
	game->physics->GetWorld()->DestroyJoint(joint);
}
