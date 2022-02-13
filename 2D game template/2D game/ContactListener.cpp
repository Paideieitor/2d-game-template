#include "ContactListener.h"
#include "Physics.h"
#include "PhysicsComponent.h"
#include "Game.h"
#include "BOX2D/Box2D/Box2D.h"
#include <string>


void ContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* body1 = fixtureA->GetBody();
    b2Body* body2 = fixtureB->GetBody();

    PhysicsComponent* PhysObjA = (PhysicsComponent*)fixtureA->GetUserData();
    PhysicsComponent* PhysObjB = (PhysicsComponent*)fixtureB->GetUserData();

    if (!std::strcmp(PhysObjB->GetTag(), "player_sensor"))
    {
        std::cout << "FLOOR" << "\n";
        PhysObjB->inAir = false;
    }
    //std::cout << "BeginContact: " << PhysObjA->GetTag() << " <- and -> " << PhysObjB->GetTag() << "\n";
}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* body1 = fixtureA->GetBody();
    b2Body* body2 = fixtureB->GetBody();

    PhysicsComponent* PhysObjA = (PhysicsComponent*)fixtureA->GetUserData();
    PhysicsComponent* PhysObjB = (PhysicsComponent*)fixtureB->GetUserData();

    if (!std::strcmp(PhysObjB->GetTag(), "player_sensor"))
    {
        std::cout << "AIR" << "\n";
        PhysObjB->inAir = true;
    }

    //std::cout << "EndContact: " << PhysObjA->GetTag() << " <- and -> " << PhysObjB->GetTag() << "\n";
}
