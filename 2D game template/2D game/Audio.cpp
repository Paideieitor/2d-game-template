#include "Audio.h"

#include "AssetManager.h"

#include "SDL/include/SDL.h"
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
	LoadMusic("audio/music/music.ogg");
	LoadMusic("audio/music/music1.ogg");

	//Loading SFX number 0
	LoadSFX("audio/sfx/sfx.wav");

	//Playing SFX number 0 with 0 repetition
	PlaySFX(0,-1);
	
	//Playing music number 1
	PlayMusic(0);

	SetMusicVolume(node.attribute("music").as_int());
	SetSfxVolume(sfxvolume = node.attribute("sfx").as_int());

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
	Music* music = new Music;
	music->song = Mix_LoadMUS_RW(game->assets->Load(path, &music->buffer), 1);

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
	Sfx* sfx = new Sfx;
	sfx->sfx = Mix_LoadWAV_RW(game->assets->Load(path, &sfx->buffer), 1);


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
	if(soundEffect > (int)soundList.size() - 1)
	{
		printf("Bad thing -> Sound effect is out of range");
	}
	else
	{
		Mix_PlayChannel(-1, soundList[soundEffect]->sfx, repetition);
	}

}

void Audio::PlayMusic(int music)
{
	if(music > (int)musicList.size() - 1)
	{
		printf("Bad thing -> Music is out of range");
	}
	else
	{
		Mix_PlayMusic(musicList[music]->song, -1);
	}

}

void Audio::SetMusicVolume(int volume)
{
	musicvolume = volume;

	node.attribute("music").set_value(musicvolume);
	game->document.save_file("config.xml");

	Mix_VolumeMusic((int)(musicvolume * audioVolumeOffset));
}

void Audio::SetSfxVolume(int volume)
{
	sfxvolume = volume;

	node.attribute("sfx").set_value(sfxvolume);
	game->document.save_file("config.xml");

	for (size_t k = 0; k < soundList.size(); k++)
	{
		Mix_VolumeChunk(soundList[k]->sfx, (int)(sfxvolume * audioVolumeOffset));
	}
}

void Audio::FreeSFX()
{
	for(size_t i = 0; i < soundList.size(); i++)
	{
		Mix_FreeChunk(soundList[i]->sfx);
		delete soundList[i]->buffer;
	}
}

void Audio::FreeMusic()
{
	for (size_t i = 0; i < musicList.size(); i++)
	{
		Mix_FreeMusic(musicList[i]->song);
		delete musicList[i]->buffer;
	}
}
