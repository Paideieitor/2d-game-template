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

	void LoadMusic();
	void LoadSFX();

	int GetMusicVolume() { return musicvolume; }
	int GetSfxVolume() { return sfxvolume; }

	void SetMusicVolume(int);
	void SetSfxVolume(int);

private:

	int musicvolume;
	int sfxvolume;


	Mix_Music* music = nullptr;


	Mix_Chunk* sfx = nullptr;


	pugi::xml_node node;
};
