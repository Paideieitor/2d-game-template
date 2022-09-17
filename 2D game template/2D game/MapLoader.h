#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Module.h"

class MapLoader : public Module
{
public:

	MapLoader();
	~MapLoader();

	void LoadMap(const char* mapName);
	

private:

	pugi::xml_document map;

	float objectFriction = 0.15;
	float boxesFrition = 0.15;

};

#endif