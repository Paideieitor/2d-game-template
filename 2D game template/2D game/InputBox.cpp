#include "UIElements.h"

#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Scenes.h"

InputBox::InputBox(string name, TTF_Font* font, fpoint position, ipoint size, color maincolor, bool worldposition, UIElement* manager)
{
	this->name = name;
	this->font = font;
	this->position = position;
	this->size = size;
	color buttoncolor = maincolor;
	this->worldposition = worldposition;
	
	if (manager)
		scene = nullptr;
	this->manager = manager;

	frame = new Button("", nullptr, position, size, buttoncolor, SINGLECLICK, worldposition, this);

	current = 0;
	getinput = false;
}

InputBox::~InputBox()
{
	if (text)
		game->textures->Unload(text);

	delete frame;
}

elementstate InputBox::Update(float dt)
{
	if (game->input->GetButton(1) == DOWN && frame->state == NOTPRESSED)
		getinput = false;

	char textinput;
	if (getinput && game->input->GetTextInput(textinput))
	{
		if (content == "" && textinput == ' ') {}
		else
		{
			string::iterator itr = content.begin() + current;
			content.insert(itr, textinput);
			current++;
		}
	}
	else if (game->input->GetKey(SDL_SCANCODE_LEFT) == DOWN)
	{
		if (current != 0)
			current--;
	}
	else if (game->input->GetKey(SDL_SCANCODE_RIGHT) == DOWN)
	{
		if (current != content.size())
			current++;
	}
	else if (game->input->GetKey(SDL_SCANCODE_BACKSPACE) == DOWN)
	{
		if (current != 0)
		{
			string::iterator itr = content.begin() + current - 1;
			content.erase(itr);
			current--;
		}
	}
	else if (game->input->GetKey(SDL_SCANCODE_RETURN) == DOWN)
	{
		if (getinput && content != "")
			if (!manager && scene)
				scene->UIEvent(this);
			else
				manager->UIEvent(this);
	}

	if (text)
		game->textures->Unload(text);

	if (content != "")
	{
		string buffer = content;
		if (getinput)
		{
			string::iterator itr = buffer.begin() + current;
			buffer.insert(itr, '|');
		}
		text = game->textures->LoadText(font, buffer.c_str(), { 0,0,0,255 }, textsize);

		ipoint p = { 0,0 };
		ipoint s = textsize;
		if (s.x > size.x)
		{
			s.x = size.x;
			if (getinput)
				p.x = textsize.x - size.x;
		}

		game->render->AddTextureEvent(21, text, position, p.x, p.y, s.x, s.y, false, 255, worldposition);
	}

	return OK;
}

bool InputBox::CleanUp()
{
	return true;
}

void InputBox::UIEvent(UIElement* element)
{
	if (element == frame)
		getinput = true;
}

string InputBox::GetContent()
{
	string output = content;

	content.erase(content.begin(), content.end());
	current = 0;

	return output;
}