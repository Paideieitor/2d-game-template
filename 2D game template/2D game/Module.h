#ifndef MODULE_H
#define MODULE_H

#include "Game.h"

class Module
{
public:

	Module() { active = true; }
	virtual ~Module() {}

	virtual bool SetUp(pugi::xml_node&) { return true; }

	virtual bool Start() { return true; }
	virtual bool Update(float dt) { return true; }
	virtual bool CleanUp() { return true; }

	void Init() { active = true; }
	void Deinit() { active = false; }

	string name;

protected:

	bool active;
};

#endif
