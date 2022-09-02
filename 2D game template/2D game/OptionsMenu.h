#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "Scene.h"

class Button;
class ButtonArray;
class Scrollbar;

class OptionsMenu : public Scene
{
public:

	OptionsMenu();
	~OptionsMenu();

	bool Start() override { return true; };
	bool Update(float dt) override;
	bool CleanUp() override { return true; };

	void UIEvent(UIElement*) override;

private:

	FontPtr buttonfont = nullptr;

	Scrollbar* fpscap = nullptr;
	Button* fullscreen = nullptr;
	Button* showCollider = nullptr;
	Button* borderless = nullptr;
	ButtonArray* resolution = nullptr;
	Scrollbar* music = nullptr;
	Scrollbar* sfx = nullptr;
	Button* tomenu = nullptr;

	std::map<unsigned int, bool> disablelist;
};

#endif
