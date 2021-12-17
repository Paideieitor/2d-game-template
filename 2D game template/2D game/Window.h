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

	void SetTitle(const char* title);
	void SetState(windowstate state);
	void SetGrabbed(bool enable);
	void SetFullscreen(bool enable);
	void SetBorderless(bool enable);
	void SetWindowSize(ipoint size);

	void CenterWindowPosition();

	const float GetScale() const { return scale; }

private:
	SDL_Window* window;

	windowstate state;

	int width;
	int height;
	float scale;

	bool grabbed;

	friend class Render;
};

#endif
