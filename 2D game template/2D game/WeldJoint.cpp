#include "WeldJoint.h"
#include "Physics.h"
#include "Game.h"
#include "BOX2D/Box2D/Box2D.h"

WeldJoint::WeldJoint(b2Body* bodyA, b2Body* bodyB,ipoint localAnchorA, ipoint localAnchorB,float referenceAngle, float dampingRatio, float frequency, bool collideConnected)
{
	b2WeldJointDef jointDef;
	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;

	jointDef.dampingRatio = dampingRatio;
	jointDef.frequencyHz = frequency;
	jointDef.localAnchorA = b2Vec2(localAnchorA.x, localAnchorA.y);
	jointDef.localAnchorB = b2Vec2(localAnchorB.x, localAnchorB.y);
	jointDef.referenceAngle = referenceAngle;
	jointDef.collideConnected = collideConnected;

	joint = (b2WeldJoint*)game->physics->GetWorld()->CreateJoint(&jointDef);
}

WeldJoint::~WeldJoint()
{
	game->physics->GetWorld()->DestroyJoint(joint);
}
