#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "UIElement.h"

class Texture;
class Button;

class InputBox : public UIElement
{
public:

	InputBox() = delete;
	InputBox(string name, Font* font, fpoint position, ipoint size, Color maincolor, bool worldposition = false, Observer observer = Observer());
	~InputBox();

	elementstate Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	string GetContent();

private:

	Texture* text;
	fpoint textposition;

	string content;
	int current;
	bool getinput;

	Button* frame;
};

#endif
