#ifndef UIELEMENTS_H
#define UIELEMENTS_H

#include "Game.h"

#include "Observer.h"

class Font;

enum elementstate
{
	OK,
	ERROR,
	CHILD_CREATION,
	CHILD_DESTRUCTION
};

enum elementtype
{
	BUTTON,
	BUTTONARRAY,
	SCROLLBAR
};

class UIElement
{
public:

	UIElement(Observer observer);
	virtual ~UIElement();

	virtual elementstate Update(float dt) = 0;
	virtual bool CleanUp() = 0;

	virtual void UIEvent(UIElement*) {}

	bool clickable;

	string name;
	elementtype type;
	Color maincolor;
	Font* font;

	fpoint position;
	ipoint size;

	bool worldposition;

protected:

	Observer observer;
};

#endif
