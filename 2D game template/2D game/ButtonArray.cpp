#include "UIElements.h"

#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Scenes.h"

ButtonArray::ButtonArray(string name, TTF_Font* font, fpoint position, ipoint size, color maincolor, TTF_Font* subfont, bool worldposition)
{
	type = BUTTONARRAY;

	maintext = game->textures->LoadText(font, name.c_str(), { 0,0,0,255 }, mainsize);

	mainposition = game->Center(mainsize, position, { (int)size.x/2,(int)size.y });

	this->name = name;
	this->position = position;
	this->size = size;
	this->maincolor = maincolor;
	this->worldposition = worldposition;

	displaying = false;

	if(subfont)
		this->subfont = subfont;
	else
		this->subfont = font;

	pugi::xml_node arraynode = game->scenes->mainnode.child(scene->name.c_str()).child(name.c_str());

	current = arraynode.attribute("current").as_int();

	amount = 0;
	pugi::xml_node button = arraynode.first_child();
	for (button; button != NULL; button = button.next_sibling())
		amount++;
	button = arraynode.first_child();

	buttonsdata = new string[amount];
	for (int i = 0; i < amount; i++)
	{
		buttonsdata[i] = button.attribute("name").as_string();
		button = button.next_sibling();
	}

	currentposition = { position.x + size.x / 2, position.y };
	currentsize = { size.x / 2, size.y };
	mainbutton = new Button(buttonsdata[current].c_str(), this->subfont, currentposition, currentsize, maincolor + 100, LOCKONCLICK, worldposition, this);
}

ButtonArray::~ButtonArray()
{
	if(buttons)
		delete[] buttons;
	delete[] buttonsdata;

	game->textures->Unload(maintext);

	delete mainbutton;
}

elementstate ButtonArray::Update(float dt)
{
	elementstate output = OK;

	if (displaying)
	{
		if (!buttons)
		{
			output = CHILD_CREATION;
			buttons = new Button[amount];

			fpoint pos = currentposition;
			for (int i = 0; i < amount; i++)
			{
				pos.y += currentsize.y;
				buttons[i].Set(buttonsdata[i], subfont, pos, currentsize, maincolor + 100, SINGLECLICK, worldposition, this);
			}
		}
	}
	else
		if (buttons)
		{
			output = CHILD_DESTRUCTION;
			delete[] buttons;
			buttons = nullptr;
		}

	game->render->AddRectangleEvent(20, position, size.x/2, size.y, maincolor, worldposition);
	game->render->AddTextureEvent(20, maintext, mainposition, 0, 0, mainsize.x, mainsize.y, false, maincolor.a, worldposition);

	if(displaying)
		displaying = false;
	return output;
}

bool ButtonArray::CleanUp()
{
	return true;
}

void ButtonArray::UIEvent(UIElement* element)
{
	if (element == mainbutton)
	{
		displaying = true;
	}

	if (displaying)
		for (int i = 0; i < amount; i++)
			if (element == &buttons[i])
			{
				current = i;
				mainbutton->name = buttons[i].name;
				mainbutton->text = buttons[i].text;
				mainbutton->textsize = buttons[i].textsize;

				pugi::xml_node arraynode = game->scenes->mainnode.child(scene->name.c_str()).child(name.c_str());

				arraynode.attribute("current").set_value(current);
				game->document.save_file("config.xml");

				mainbutton->state = NOTPRESSED;
				displaying = false;

				scene->UIEvent(this);
				break;
			}
}

string ButtonArray::GetArrayCurrent() 
{
	return mainbutton->name;
}