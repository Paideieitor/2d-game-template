#include "Module.h"

class Audio : public Module
{
public:

	Audio();
	~Audio();

	bool SetUp(pugi::xml_node&);
	bool Update(float dt);
	bool CleanUp();

	void SetMusicVolume(int);
	void SetSfxVolume(int);

	int musicvolume;
	int sfxvolume;

private:

	pugi::xml_node node;
};
