#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Module.h"

class MapLoader : public Module
{
public:

	MapLoader();
	~MapLoader();

	bool SetUp(pugi::xml_node&);
	bool Update(float dt);
	bool CleanUp();

	void LoadMap(const char* mapName);
	

private:

	pugi::xml_document document;

};

#endif