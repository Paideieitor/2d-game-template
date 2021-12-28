#include "AssetManager.h"

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
	CreatePath("Assets.zip");

	return true;
}

bool AssetManager::CreatePath(const char* newDir, const char* mount_point)
{
	if (PHYSFS_addToSearchPath(newDir, 1) == 0)
		cout << "Asset Manager path creation -> Bad Thing, Error in " << newDir << " -> " << PHYSFS_getLastError() << endl;
	else
		return false;

	return true;
}

bool AssetManager::Exists(const char* file) const
{
	return PHYSFS_exists(file);
}

unsigned int AssetManager::LoadData(const char* file, char** buffer) const
{
	unsigned int output = 0;

	PHYSFS_file* data_file = PHYSFS_openRead(file);									

	if (data_file != nullptr)
	{
		PHYSFS_sint64 file_lenght = PHYSFS_fileLength(data_file);
		*buffer = new char[(unsigned int)file_lenght];
		PHYSFS_sint64 readed = PHYSFS_read(data_file, *buffer, 1, (PHYSFS_uint32)file_lenght);
		if (readed != file_lenght)													
		{	
			cout << "Asset Manager data loading -> Bad Thing, Error in " << file << " -> " << PHYSFS_getLastError() << endl;
			delete buffer;														
		}
		else
			output = (unsigned int)readed;
				
		PHYSFS_close(data_file);													
	}
	else
		cout << "Asset Manager file opening -> Bad Thing, Error in " << file << " -> " << PHYSFS_getLastError() << endl;

	return output;
}

SDL_RWops* AssetManager::Load(const char* file, char** buffer) const
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

pugi::xml_parse_result AssetManager::LoadXML(pugi::xml_document &data_file, const char* path)
{
	char* buffer;
	unsigned int file_size = LoadData(path, &buffer);
	pugi::xml_parse_result result = data_file.load_buffer(buffer, file_size);
	delete[] buffer;

	return result;
}
