#ifndef SCENES_H
#define SCENES_H

#include "Game.h"
#include "Point.h"
#include "Color.h"
#include "UI.h"
#include "Textures.h"

class Scene
{
public:

	Scene() {}
	virtual ~Scene() {}

	virtual bool Start() = 0;
	virtual bool Update(float dt) = 0;
	virtual bool CleanUp() = 0;

	virtual void UIEvent(UIElement*) {}

	string name;
};

class MainMenu : public Scene
{
public:

	MainMenu();
	~MainMenu();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	Color* background;

private:

	Texture* test;

	Font* buttonfont;

	Button* tooptions;
	Button* exit;

	InputBox* box;
};

class OptionsMenu : public Scene
{
public:

	OptionsMenu();
	~OptionsMenu();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	Color* background;

private:

	Font* buttonfont;

	Button* fullscreen;
	Button* borderless;
	ButtonArray* resolution;
	Scrollbar* music;
	Scrollbar* sfx;
	Button* tomenu;

};

#endif