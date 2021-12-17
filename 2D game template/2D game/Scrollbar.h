#ifndef SCROLLBAR_ARRAY_H
#define SCROLLBAR_ARRAY_H

#include "UIElement.h"

class Texture;
class Button;

class Scrollbar : public UIElement
{
public:

	Scrollbar() = delete;
	Scrollbar(string name, Font* font, fpoint position, ipoint size, Color maincolor, float start = 0.0f, Font* valuefont = nullptr, bool worldposition = false, Observer observer = Observer());
	~Scrollbar();

	elementstate Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	float GetBarValue();

	Button* scroll;

	Texture* text;
	fpoint textposition;

	Font* valuefont;
	Texture* valuetext;
	fpoint valueposition;

	float value;
	bool updatevalue;
};

#endif
