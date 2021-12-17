#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include "UIElement.h"

class Texture;
class Button;

class ButtonArray : public UIElement
{
public:

	ButtonArray() = delete;
	ButtonArray(string name, Font* font, fpoint position, ipoint size, Color buttoncolor, Font* subfont = nullptr, bool worldposition = false);
	~ButtonArray();

	elementstate Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	string GetArrayCurrent();

	bool displaying;
	int current;

	Texture* maintext;
	fpoint mainposition;

	fpoint currentposition;
	ipoint currentsize;

	Font* subfont;

	Button* mainbutton;

	int amount;
	string* buttonsdata;
	Button* buttons;
};

#endif
