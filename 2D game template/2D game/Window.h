#ifndef WINDOW_H
#define WINDOW_H

#include "Module.h"

enum class windowstate
{
	QUIT,
	HIDE,
	SHOW
};

class Window : public Module
{
public:

	Window();
	virtual ~Window();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	SDL_Window* window;

	windowstate state;

	int width;
	int height;
	float scale;

	bool grabbed;
};

#endif
