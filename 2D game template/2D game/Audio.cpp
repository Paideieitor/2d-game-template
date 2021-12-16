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

	//Loading music number 0 and 1
	LoadMusic("AudioTest/music.ogg");
	LoadMusic("AudioTest/music1.ogg");

	//Loading SFX number 0
	LoadSFX("AudioTest/sfx.wav");

	//Playing SFX number 0 with 0 repetition
	PlaySFX(0,-1);
	
	//Playing music number 1
	PlayMusic(1);

	return true;
}

bool Audio::Update(float dt)
{
	return true;
}

bool Audio::CleanUp()
{
	FreeSFX();
	FreeMusic();
	Mix_Quit();

	return true;
}

void Audio::LoadMusic(const char* path)
{
	Mix_Music* music = Mix_LoadMUS(path);
	if (music == nullptr)
	{
		printf("Bad thing -> Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else 
	{
		musicList.push_back(music);
	}
	
}

void Audio::LoadSFX(const char* path)
{
	Mix_Chunk* sfx = Mix_LoadWAV(path);
	if (sfx == nullptr)
	{
		printf("Bad thing -> Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else
	{
		soundList.push_back(sfx);
	}
}

void Audio::PlaySFX(int soundEffect, int repetition)
{
	if(soundEffect > soundList.size() - 1)
	{
		printf("Bad thing -> Sound effect is out of range");
	}
	else
	{
		Mix_PlayChannel(-1, soundList[soundEffect], repetition);
	}

}

void Audio::PlayMusic(int music)
{
	if(music > musicList.size() - 1)
	{
		printf("Bad thing -> Music is out of range");
	}
	else
	{
		Mix_PlayMusic(musicList[music], -1);
	}

}

void Audio::SetMusicVolume(int volume)
{
	musicvolume = volume;

	node.attribute("music").set_value(musicvolume);
	game->document.save_file("config.xml");

	Mix_VolumeMusic(musicvolume * audioVolumeOffset);
}

void Audio::SetSfxVolume(int volume)
{
	sfxvolume = volume;

	node.attribute("sfx").set_value(sfxvolume);
	game->document.save_file("config.xml");

	for (int k = 0; k < soundList.size(); k++)
	{
		Mix_VolumeChunk(soundList[k], sfxvolume * audioVolumeOffset);
	}
}

void Audio::FreeSFX()
{
	for(int i = 0; i < soundList.size(); i++)
	{
		Mix_FreeChunk(soundList[i]);
	}
}

void Audio::FreeMusic()
{
	for (int i = 0; i < musicList.size(); i++)
	{
		Mix_FreeMusic(musicList[i]);
	}
}
