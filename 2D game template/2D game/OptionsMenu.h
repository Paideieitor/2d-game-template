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

	bool Start() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	void UIEvent(UIElement*) override;

private:

	FontPtr buttonfont;

	Button* fullscreen;
	Button* borderless;
	ButtonArray* resolution;
	Scrollbar* music;
	Scrollbar* sfx;
	Button* tomenu;

};

#endif
