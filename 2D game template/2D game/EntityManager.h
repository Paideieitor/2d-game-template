#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Module.h"

class Entity;

class EntityManager : public Module
{
public:

	EntityManager();
	~EntityManager();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

private:

	void AddEntity(Entity*);
	void EraseEntity(Entity*);

private:

	std::vector<std::pair<bool, Entity*>> entities;
	std::vector<Entity*> addentities;

	friend class Entity;
};

#endif
