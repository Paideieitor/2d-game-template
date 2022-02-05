#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Module.h"

#include "Player.h"
#include "Camera.h"

class EntityManager : public Module
{
public:

	EntityManager();
	~EntityManager();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	Player* AddPlayer(const std::string& name, const fpoint& position, float rotation);
	Camera* AddCamara(const fpoint& position);
	void EraseEntity(Entity*);

private:

	std::vector<std::pair<bool, Entity*>> entities;
	std::vector<Entity*> addentities;
};

#endif
