#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "Scene.h"

class StudioScene : public Scene
{
public:

	StudioScene(float duration);
	~StudioScene();

	bool Start() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	void UIEvent(UIElement*) override;

private:

	TexturePtr logoTexture;
	float duration;
	bool fadingOut = false;
};

#endif
