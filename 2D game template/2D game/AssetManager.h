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

	bool Exists(const std::string& file) const;

	unsigned int LoadData(const std::string& file, char** buffer) const;
	SDL_RWops* Load(const std::string& file, char** buffer) const;

	pugi::xml_parse_result LoadXML(pugi::xml_document &data_file, const std::string& path);

private:

	bool CreatePath(const char* newDir);
};

#endif