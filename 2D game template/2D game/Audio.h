#include "Module.h"
#include "MIX/include/SDL_mixer.h"

class Audio : public Module
{
public:

	Audio();
	~Audio();

	bool SetUp(pugi::xml_node&);
	bool Update(float dt);
	bool CleanUp();

	void LoadMusic(const char* path);
	void LoadSFX(const char* path);

	void PlaySFX(int soundEffect, int repetition);
	void PlayMusic(int music);

	int GetMusicVolume() { return musicvolume; }
	int GetSfxVolume() { return sfxvolume; }

	void SetMusicVolume(int);
	void SetSfxVolume(int);

	void UpdateVolume();

private:

	void FreeSFX();
	void FreeMusic();

	float audioVolumeOffset = 1.28;

	int musicvolume;
	int sfxvolume;

	std::vector<Mix_Music*> musicList;
	std::vector<Mix_Chunk*> soundList;


	pugi::xml_node node;
};
