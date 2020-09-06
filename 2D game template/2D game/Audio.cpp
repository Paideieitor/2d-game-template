#include "Audio.h"

#include "MIX/include/SDL_mixer.h"
#pragma comment ( lib, "MIX/lib/SDL2_mixer.lib" )

Audio::Audio()
{
	name = "audio";
}

Audio::~Audio()
{
	Mix_Quit();
}

bool Audio::SetUp(pugi::xml_node& node)
{
	this->node = node;

	musicvolume = node.attribute("music").as_int();
	sfxvolume = node.attribute("sfx").as_int();

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0)
	{
		cout << "Audio -> Bad Thing, Error:" << Mix_GetError() << endl;
		return false;
	}

	return true;
}

bool Audio::Update(float dt)
{
	return true;
}

bool Audio::CleanUp()
{
	return true;
}

void Audio::SetMusicVolume(int volume)
{
	musicvolume = volume;

	node.attribute("music").set_value(musicvolume);
	game->document.save_file("config.xml");
}

void Audio::SetSfxVolume(int volume)
{
	sfxvolume = volume;

	node.attribute("sfx").set_value(sfxvolume);
	game->document.save_file("config.xml");
}