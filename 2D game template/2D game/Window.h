#ifndef WINDOW_H
#define WINDOW_H

#include "Module.h"

typedef struct SDL_Window WindowData;

class Window : public Module
{
public:

	enum class State
	{
		QUIT,
		HIDE,
		SHOW
	};

public:

	Window();
	virtual ~Window();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void SetTitle(const char* title);
	void SetState(Window::State state);

	const bool IsFullscreen() const { return fullscreen; }
	void SetFullscreen(bool enable);
	const bool IsBorderless() const { return borderless; }
	void SetBorderless(bool enable);
	const bool IsGrabbed() const { return grabbed; }
	void SetGrabbed(bool enable);

	const ipoint GetWindowSize() { return size; }
	void SetWindowSize(const ipoint& size);

	void CenterWindowPosition();

private:

	WindowData* window;

	Window::State state;

	ipoint size;

	bool fullscreen;
	bool borderless;
	bool grabbed;

	pugi::xml_node node;

	friend class Render;
};

#endif
