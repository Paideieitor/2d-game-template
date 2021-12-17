#ifndef BUTTON_H
#define BUTTON_H

#include "UIElement.h"

class Texture;

enum buttontype
{
	SINGLECLICK,
	LOCKONCLICK,
	REPEATPRESS
};

enum buttonstate
{
	NOTPRESSED,
	PRESSED,
	HOVER
};

class Button : public UIElement
{
public:

	Button();
	Button(string name, Font* font, fpoint position, ipoint size, Color maincolor, buttontype presstype = SINGLECLICK, bool worldposition = false, Observer observer = Observer());
	~Button();

	void Set(string name, Font* font, fpoint position, ipoint size, Color maincolor, buttontype presstype = SINGLECLICK, bool worldposition = false, Observer observer = Observer());

	elementstate Update(float dt);
	bool CleanUp();

	Texture* text;
	fpoint textposition;

	buttonstate state;

	buttontype presstype;
};

#endif
