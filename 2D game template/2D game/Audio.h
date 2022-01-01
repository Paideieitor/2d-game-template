#include "Module.h"

struct _Mix_Music;
typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;


struct Music 
{
	Mix_Music* song = nullptr;
	char* buffer = nullptr;
};

struct Sfx
{
	Mix_Chunk* sfx = nullptr;
	char* buffer = nullptr;
};

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

private:

	void FreeSFX();
	void FreeMusic();

	float audioVolumeOffset = 1.28f;

	int musicvolume;
	int sfxvolume;

	std::vector<Music*> musicList;
	std::vector<Sfx*> soundList;


	pugi::xml_node node;
};
