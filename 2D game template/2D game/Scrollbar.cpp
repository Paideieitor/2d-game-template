#include "UIElements.h"

#include "Render.h"
#include "Input.h"
#include "Window.h"
#include "Scenes.h"

Scrollbar::Scrollbar(string name, TTF_Font* font, fpoint position, ipoint size, color maincolor, float start, TTF_Font* valuefont, bool worldposition, UIElement* manager)
{
	type = SCROLLBAR;

	this->name = name;
	this->font = font;
	this->position = position;
	this->size = size;
	this->maincolor = maincolor;
	this->worldposition = worldposition;

	text = game->textures->LoadText(font, name.c_str(), { 0,0,0,255 }, this->textsize);
	textposition = { position.x, position.y - textsize.y };

	this->valuefont = valuefont;
	value = start;
	if (value < 0)
		value = 0;
	else if (value > 100)
		value = 100;
	updatevalue = false;

	ipoint scrollsize = {size.x/20, (int)(size.y * 2)};
	fpoint scrollposition = { (position.x + value * (size.x / 100)) - scrollsize.x / 2, position.y - scrollsize.y / 4 };
	scroll = new Button("", nullptr, scrollposition, scrollsize, maincolor + 100, REPEATPRESS, worldposition, this);

	if (valuefont)
	{
		valuetext = game->textures->LoadText(valuefont, game->IntToString((int)value).c_str(), { 0,0,0,255 }, valuesize);
		valueposition = { position.x + size.x + scrollsize.x / 1.5f, position.y - valuesize.y / 2 };
	}
	else
		valuetext = nullptr;

	if (manager)
		scene = nullptr;
	this->manager = manager;
}

Scrollbar::~Scrollbar()
{
	game->textures->Unload(text);
	game->textures->Unload(valuetext);

	delete scroll;
}

elementstate Scrollbar::Update(float dt)
{
	game->render->AddRectangleEvent(20, position, size.x, size.y, maincolor, worldposition);
	game->render->AddTextureEvent(20, text, textposition, 0, 0, textsize.x, textsize.y);

	if (valuetext)
	{
		if (updatevalue)
		{
			updatevalue = false;
			game->textures->Unload(valuetext);
			valuetext = game->textures->LoadText(valuefont, game->IntToString((int)value).c_str(), { 0,0,0,255 }, valuesize);
		}
		game->render->AddTextureEvent(20, valuetext, valueposition, 0, 0, valuesize.x, valuesize.y);
	}

	return OK;
}

bool Scrollbar::CleanUp()
{
	return true;
}

void Scrollbar::UIEvent(UIElement* element)
{
	if (element == scroll)
	{
		fpoint mouseposition = game->input->GetMousePos(worldposition);

		if (worldposition)
		{
			fpoint camera = { (float)-game->render->camera.x, (float)-game->render->camera.y };
			camera /= game->window->scale;

			mouseposition = camera + mouseposition;
		}

		scroll->position.x = mouseposition.x - scroll->size.x / 2;

		float pastvalue = value;
		value = ((mouseposition.x - position.x) / size.x) * 100;

		if (value < 0)
		{
			value = 0;
			scroll->position.x = position.x - scroll->size.x / 2;
		}
		else if (value > 100)
		{
			value = 100;
			scroll->position.x = (position.x + size.x) - scroll->size.x / 2;
		}

		if (valuetext && (int)pastvalue != (int)value)
			updatevalue = true;

		if (scene)
			scene->UIEvent(this);
		else
			manager->UIEvent(this);
	}
}

float Scrollbar:: GetBarValue()
{
	return value; 
}