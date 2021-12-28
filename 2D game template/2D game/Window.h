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

	const bool IsFullscreen() const { return fullscreen; }
	void SetFullscreen(bool enable);
	const bool IsBorderless() const { return borderless; }
	void SetBorderless(bool enable);
	const bool IsGrabbed() const { return grabbed; }
	void SetGrabbed(bool enable);

	void SetWindowSize(ipoint size);

	void CenterWindowPosition();

	const float GetScale() const { return scale; }
	void SetScale(float scale) { this->scale = scale; }

private:
	SDL_Window* window;

	windowstate state;

	int width;
	int height;
	float scale;

	bool fullscreen;
	bool borderless;
	bool grabbed;

	pugi::xml_node node;

	friend class Render;
};

#endif
