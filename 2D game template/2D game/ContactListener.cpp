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
            PhysObjB->contacts.push_back(PhysObjA);
    }
    
    if(!std::strcmp(PhysObjB->GetTag(), "grab_sensor"))
    {
        if (!std::strcmp(PhysObjA->GetTag(), "block"))
        {
            PhysObjB->contacts.push_back(PhysObjA);
        }
    }

    if (!std::strcmp(PhysObjB->GetTag(), "grab_sensor"))
    {
        if (!std::strcmp(PhysObjA->GetTag(), "end"))
        {
            PhysObjB->inVine = true;
        }
    }

    if (!std::strcmp(PhysObjB->GetTag(), "player"))
    {
        if (!std::strcmp(PhysObjA->GetTag(), "vine")) 
        {
            PhysObjB->inVine = true;
        }
    }
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
        for (int i = 0; i < PhysObjB->contacts.size(); i++) 
        {
            if (PhysObjB->contacts[i] == PhysObjA) 
            {
                PhysObjB->contacts.erase(PhysObjB->contacts.begin() + i);
            }
        }
    }

    if (!std::strcmp(PhysObjB->GetTag(), "grab_sensor"))
    {
        for (int i = 0; i < PhysObjB->contacts.size(); i++)
        {
            if (PhysObjB->contacts[i] == PhysObjA)
            {
                PhysObjB->contacts.erase(PhysObjB->contacts.begin() + i);
            }
        }
    }

    if (!std::strcmp(PhysObjB->GetTag(), "player"))
    {
        if (!std::strcmp(PhysObjA->GetTag(), "vine"))
        {
            PhysObjB->inVine = false;
        }
    }
}
