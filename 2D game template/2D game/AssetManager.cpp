#include "AssetManager.h"

#include "SDL/include/SDL_rwops.h"
#include "PFS/include/physfs.h"
#pragma comment( lib, "PFS/lib/physfs.lib" )

AssetManager::AssetManager() : Module()
{
	name = ("asset_manager");

	PHYSFS_init(nullptr);
}

AssetManager::~AssetManager()
{
	PHYSFS_deinit();
}

bool AssetManager::SetUp(pugi::xml_node& node)
{
	CreatePath("Assets");

	return true;
}

bool AssetManager::CreatePath(const char* newDir)
{
	if (PHYSFS_addToSearchPath(newDir, 1) == 0)
		game->Log("Asset Manager path creation -> Bad Thing, Error in " + std::string(newDir) + " -> " + std::string(PHYSFS_getLastError()));
	else
		return false;

	return true;
}

bool AssetManager::Exists(const std::string& file) const
{
	return PHYSFS_exists(file.c_str());
}

unsigned int AssetManager::LoadData(const std::string& file, char** buffer) const
{
	unsigned int output = 0;

	PHYSFS_file* data_file = PHYSFS_openRead(file.c_str());									

	if (data_file != nullptr)
	{
		PHYSFS_sint64 file_lenght = PHYSFS_fileLength(data_file);
		*buffer = new char[(unsigned int)file_lenght];
		PHYSFS_sint64 readed = PHYSFS_read(data_file, *buffer, 1, (PHYSFS_uint32)file_lenght);
		if (readed != file_lenght)													
		{	
			game->Log("Asset Manager data loading -> Bad Thing, Error in " + file + " -> " + std::string(PHYSFS_getLastError()));
			delete buffer;														
		}
		else
			output = (unsigned int)readed;
				
		PHYSFS_close(data_file);													
	}
	else
		game->Log("Asset Manager file opening -> Bad Thing, Error in " + file + " -> " + std::string(PHYSFS_getLastError()));

	return output;
}

SDL_RWops* AssetManager::Load(const std::string& file, char** buffer) const
{
	int size = LoadData(file, buffer);

	if (size > 0)
	{
		SDL_RWops* r = SDL_RWFromConstMem(*buffer, size);

		return r;
	}
	else
		return nullptr;
}

pugi::xml_parse_result AssetManager::LoadXML(pugi::xml_document &data_file, const std::string& path)
{
	char* buffer;
	unsigned int file_size = LoadData(path, &buffer);
	pugi::xml_parse_result result = data_file.load_buffer(buffer, file_size);
	delete[] buffer;

	return result;
}
