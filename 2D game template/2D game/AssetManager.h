#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Module.h"

struct SDL_RWops;

class AssetManager : public Module
{
public:

	AssetManager();
	virtual ~AssetManager();

	bool SetUp(pugi::xml_node&);

	bool Exists(const char* file) const;

	unsigned int LoadData(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file, char** buffer) const;

	pugi::xml_parse_result LoadXML(pugi::xml_document &data_file, const char* path);

private:

	bool CreatePath(const char* newDir, const char* mount_point = nullptr);
};

#endif