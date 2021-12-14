#include "Module.h"

class Audio : public Module
{
public:

	Audio();
	~Audio();

	bool SetUp(pugi::xml_node&);
	bool Update(float dt);
	bool CleanUp();

	int GetMusicVolume() { return musicvolume; }
	int GetSfxVolume() { return sfxvolume; }

	void SetMusicVolume(int);
	void SetSfxVolume(int);

private:

	int musicvolume;
	int sfxvolume;

	pugi::xml_node node;
};
