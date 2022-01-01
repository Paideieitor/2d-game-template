#ifndef SCENES_H
#define SCENES_H

#include "Game.h"

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;
class Font;
typedef std::shared_ptr<Font> FontPtr;

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

	std::string name;
};

#endif
