#ifndef JOINT_H
#define JOINT_H

class b2DistanceJoint;
class b2Body;
enum b2JointType;


class Joint
{
public:
	Joint();
	~Joint();

	void CreateJoint(b2Body* bodyA, b2Body* bodyB, float lenght);

private:

	b2DistanceJoint* joint;
};

#endif