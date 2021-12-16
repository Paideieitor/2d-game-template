#include "Audio.h"

#include "MIX/include/SDL_mixer.h"
#include "IMG/include/SDL_image.h"
#pragma comment ( lib, "MIX/lib/SDL2_mixer.lib" )
#pragma comment ( lib, "IMG/lib/SDL2_image.lib" )

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



	//SDL Initialization stuff
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("Bad thing -> SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, /*Experimental value*/ 2048) < 0)
	{
		printf("Bad thing -> SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	LoadMusic();
	LoadSFX();


	Mix_PlayMusic(music, -1);


	return true;
}

bool Audio::Update(float dt)
{
	return true;
}

bool Audio::CleanUp()
{
	Mix_FreeChunk(sfx);
	Mix_FreeMusic(music);
	Mix_Quit();

	return true;
}

void Audio::LoadMusic()
{
	music = Mix_LoadMUS("AudioTest/music.ogg");
	if (music == nullptr)
	{
		printf("Bad thing -> Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Audio::LoadSFX()
{
	sfx = Mix_LoadWAV("AudioTest/sfx.wav");
	if (sfx == NULL)
	{
		printf("Bad thing -> Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
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