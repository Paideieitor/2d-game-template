#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "BOX2D/Box2D/Box2D.h"

class ContactListener : public b2ContactListener
{
private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif