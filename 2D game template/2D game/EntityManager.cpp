#include "EntityManager.h"

#include "Entity.h"

EntityManager::EntityManager()
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
    std::vector<int> deleteindex;

    for (size_t i = 0; i < entities.size(); ++i)
    {
        if (!entities[i].first)
        {
            deleteindex.push_back(i);
            continue;
        }

        Entity* entity = entities[i].second;

        if (!entity->Update(dt))
        {
            game->Log("EntityManager Update -> Bad Thing, Error in entity " + entity->name);
            return false;
        }
    }

    for (int i = deleteindex.size() - 1; i >= 0; --i)
    {
        delete entities[deleteindex[i]].second;
        entities.erase(entities.begin() + deleteindex[i]);
    }

    size_t i = 0;
    for (i; i < addentities.size(); ++i)
        entities.push_back(std::make_pair(true, addentities[i]));
    if (i > 0)
        addentities.clear();

    return true;
}

bool EntityManager::CleanUp()
{
    while (entities.size() != 0)
    {
        delete entities.begin()->second;
        entities.erase(entities.begin());
    }

    while (addentities.size() != 0)
    {
        delete *addentities.begin();
        addentities.erase(addentities.begin());
    }

    return true;
}

Player* EntityManager::AddPlayer(const std::string& name, const fpoint& position, float rotation)
{
    Player* output = new Player(name, position, rotation);
    addentities.push_back(output);

    return output;
}

Camera* EntityManager::AddCamara(const fpoint& position)
{
    Camera* output = new Camera(position);
    addentities.push_back(output);

    return output;
}

Rock* EntityManager::AddRock(const std::string& name, const fpoint& position, const ipoint& size, float rotation)
{
    Rock* output = new Rock(name, position, size, rotation);
    addentities.push_back(output);

	return nullptr;
}

Vine* EntityManager::AddVine(const std::string& name, const fpoint& position, const ipoint& size)
{
    Vine* output = new Vine(name, position, size);
    addentities.push_back(output);

    return nullptr;
}

void EntityManager::EraseEntity(Entity* entity)
{
    for (size_t i = 0; i < entities.size(); ++i)
        if (entity == entities[i].second)
        {
            entities[i].first = false;
            break;
        }
}
