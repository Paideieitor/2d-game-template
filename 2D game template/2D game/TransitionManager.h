#ifndef TRANSITIONMANAGER_H
#define TRANSITIONMANAGER_H

#include "Module.h"

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

enum TransitionState
{
	TRANSITION_BEGIN,
	MID_TRANSITION,
	TRANSITION_END_FADE_OUT,
	TRANSITION_END_FADE_IN
};

class TransitionManager : public Module
{
public:

	TransitionManager();
	virtual ~TransitionManager();

	bool SetUp(pugi::xml_node&);
	bool Update(float dt);
	bool CleanUp();
	
	void FadeToBlack(float duration, bool fadeIn);
	TransitionState GetState();
private:
	TransitionState state;
	float transitionTime;
	float duration;
	bool fadeIn;
	TexturePtr background;
};

#endif