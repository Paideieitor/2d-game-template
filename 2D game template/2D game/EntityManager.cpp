#include "EntityManager.h"

#include "Entity.h"

EntityManager::EntityManager() : listmodify(false)
{
    name = "entity_manager";
}

EntityManager::~EntityManager()
{
}

bool EntityManager::SetUp(pugi::xml_node&)
{
    return true;
}

bool EntityManager::Start()
{
    return true;
}

bool EntityManager::Update(float dt)
{
    listmodify = false;

    size_t counter = 0;
    bool entitiesleft = true;
    while (entitiesleft)
    {
        entitiesleft = false;
        for (size_t i = counter; i < entities.size(); ++i)
        {
            ++counter;

            if (!entities[i]->Update(dt))
            {
                game->Log("EntityManager Update -> Bad Thing, Error in entity " + entities[i]->name);
                return false;
            }

            if (listmodify)
            {
                listmodify = false;
                entitiesleft = true;
                break;
            }
        }
    }

    return true;
}

bool EntityManager::CleanUp()
{
    return true;
}

void EntityManager::AddEntity(Entity* entity)
{
    if (entity)
    {
        entities.push_back(entity);
        listmodify = true;
    }
}

void EntityManager::EraseEntity(Entity*& entity)
{
    for (size_t i = 0; i < entities.size(); ++i)
        if (entities[i] == entity)
        {
            entities.erase(entities.begin() + i);
            entity = nullptr;

            listmodify = true;
        }
}
