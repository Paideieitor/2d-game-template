#include "RevoluteJoint.h"
#include "Physics.h"
#include "Game.h"
#include "BOX2D/Box2D/Box2D.h"


RevoluteJoint::RevoluteJoint(b2Body* bodyA, b2Body* bodyB,bool enableLimit, bool collideConnected)
{
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;
	jointDef.enableLimit = enableLimit;
	jointDef.collideConnected = collideConnected;

	joint = (b2RevoluteJoint*)game->physics->GetWorld()->CreateJoint(&jointDef);
}


RevoluteJoint::~RevoluteJoint()
{
	game->physics->GetWorld()->DestroyJoint(joint);
}
