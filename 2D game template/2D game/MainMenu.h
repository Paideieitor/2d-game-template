#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Scene.h"

class Button;
class InputBox;
class Label;

class Player;
class Camera;

class MainMenu : public Scene
{
public:

	MainMenu();
	~MainMenu();

	bool Start() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	void UIEvent(UIElement*) override;

private:

	TexturePtr test;
	TexturePtr backgroundImg;

	FontPtr buttonfont;

	Button* play;
	Button* tooptions;
	Button* exit;

	InputBox* box;

	Player* player;
	Camera* camera;
};

#endif
