#ifndef UIELEMENTS_H
#define UIELEMENTS_H

#include "Game.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Textures.h"

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

	UIElement() 
	{
		clickable = false;
		game->ui->elements.push_back(this); 
		scene = game->scenes->currentscene;
	}
	virtual ~UIElement() 
	{
		game->ui->EraseElement(this);
	}

	virtual elementstate Update(float dt) = 0;
	virtual bool CleanUp() = 0;

	virtual void UIEvent(UIElement*) {}

	bool clickable;

	string name;
	elementtype type;
	color maincolor;
	TTF_Font* font;

	fpoint position;
	ipoint size;

	bool worldposition;

protected:

	Scene* scene;
	UIElement* manager;
};

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
	Button(string name, TTF_Font* font, fpoint position, ipoint size, color maincolor, buttontype presstype = SINGLECLICK, bool worldposition = false, UIElement* manager = nullptr);
	~Button();

	void Set(string name, TTF_Font* font, fpoint position, ipoint size, color maincolor, buttontype presstype = SINGLECLICK, bool worldposition = false, UIElement* manager = nullptr);

	elementstate Update(float dt);
	bool CleanUp();

	SDL_Texture* text;
	ipoint textsize;
	fpoint textposition;

	buttonstate state;

	buttontype presstype;
};

class ButtonArray : public UIElement
{
public:

	ButtonArray(string name, TTF_Font* font, fpoint position, ipoint size, color buttoncolor, TTF_Font* subfont = nullptr, bool worldposition = false);
	~ButtonArray();

	elementstate Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	string GetArrayCurrent();

	bool displaying;
	int current;

	SDL_Texture* maintext;
	fpoint mainposition;
	ipoint mainsize;

	fpoint currentposition;
	ipoint currentsize;

	TTF_Font* subfont;

	Button* mainbutton;

	int amount;
	string* buttonsdata;
	Button* buttons;

private:
};

class Scrollbar : public UIElement
{
public:

	Scrollbar(string name, TTF_Font* font, fpoint position, ipoint size, color maincolor, float start = 0.0f, TTF_Font* valuefont = nullptr, bool worldposition = false, UIElement* manager = nullptr);
	~Scrollbar();

	elementstate Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	float GetBarValue();

	Button* scroll;

	SDL_Texture* text;
	fpoint textposition;
	ipoint textsize;

	TTF_Font* valuefont;
	SDL_Texture* valuetext;
	fpoint valueposition;
	ipoint valuesize;

	float value;
	bool updatevalue;
};

class InputBox : public UIElement
{
public:

	InputBox(string name, TTF_Font* font, fpoint position, ipoint size, color maincolor, bool worldposition = false, UIElement* manager = nullptr);
	~InputBox();

	elementstate Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	string GetContent();

private:

	SDL_Texture* text;
	fpoint textposition;
	ipoint textsize;

	string content;
	int current;
	bool getinput;

	Button* frame;
};

#endif
