#ifndef SCENES_H
#define SCENES_H

#include "Game.h"

class UIElement;

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

#endif
