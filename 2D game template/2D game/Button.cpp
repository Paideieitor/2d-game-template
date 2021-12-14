#include "UIElements.h"

#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Scenes.h"

Button::Button()
{
	type = BUTTON;
	state = NOTPRESSED;
}

Button::Button(string name, Font* font, fpoint position, ipoint size, color maincolor, buttontype presstype, bool worldposition, UIElement* manager)
{
	type = BUTTON;
	state = NOTPRESSED;

	if (name != "")
	{
		text = game->textures->LoadText(font, name.c_str(), { 0,0,0,255 }, textsize);
		textposition = game->Center(textsize, position, { (int)size.x,(int)size.y });
	}
	else
		text = nullptr;

	this->name = name;
	this->font = font;
	this->position = position;
	this->size = size;
	this->maincolor = maincolor;
	this->presstype = presstype;
	this->worldposition = worldposition;

	if(manager)
		scene = nullptr;
	this->manager = manager;
}

Button::~Button()
{
	game->textures->Unload(text);
}

void Button::Set(string name, Font* font, fpoint position, ipoint size, color maincolor, buttontype presstype, bool worldposition, UIElement* manager)
{
	text = game->textures->LoadText(font, name.c_str(), { 0,0,0,255 }, textsize);

	textposition = game->Center(textsize, position, { (int)size.x,(int)size.y });

	this->name = name;
	this->position = position;
	this->size = size;
	this->maincolor = maincolor;
	this->presstype = presstype;
	this->worldposition = worldposition;

	if (manager)
		scene = nullptr;
	this->manager = manager;
}

elementstate Button::Update(float dt)
{
	elementstate output = OK;

	color color;

	if (presstype == REPEATPRESS && state == PRESSED && game->input->GetButton(1) == REPEAT) 
	{}
	else if (clickable)
	{
		if(presstype != LOCKONCLICK)
			state = HOVER;
		if (game->input->GetButton(1) == DOWN)
			if(presstype != LOCKONCLICK)
				state = PRESSED;
			else
				switch (state)
				{
				case PRESSED:
					state = NOTPRESSED;
					break;
				case NOTPRESSED:
					state = PRESSED;
					break;
				}
	}
	else if (presstype != LOCKONCLICK)
		state = NOTPRESSED;

	switch (state)
	{
	case NOTPRESSED:
		color = maincolor;
		break;
	case PRESSED:
		color = maincolor + 30;
		if (!manager && scene)
			scene->UIEvent(this);
		else
			manager->UIEvent(this);
		break;
	case HOVER:
		color = maincolor - 30;
		break;
	}

	game->render->AddRectangleEvent(20, position, size.x, size.y, color, worldposition);

	if (text)
	{
		Uint8 a;
		if (SDL_GetTextureAlphaMod(text->Get(), &a) == -1)
			text = game->textures->LoadText(font, name.c_str(), { 0,0,0,255 }, textsize);
		game->render->AddTextureEvent(20, text, textposition, 0, 0, textsize.x, textsize.y, false, color.a, worldposition);
	}

	return output;
}

bool Button::CleanUp()
{
	return true;
}