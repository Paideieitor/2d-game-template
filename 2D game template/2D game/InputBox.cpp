#include "InputBox.h"

#include "Input.h"
#include "Textures.h"
#include "Render.h"
//#include "Window.h"
//#include "Scene.h"
//
#include "Label.h"
#include "Button.h"
//
//InputBox::InputBox(string name, Font* font, fpoint position, ipoint size, Color maincolor, bool worldposition, Observer observer) : UIElement(observer)
//{
//	this->name = name;
//	this->font = font;
//	this->position = position;
//	this->size = size;
//	Color buttoncolor = maincolor;
//	this->worldposition = worldposition;
//
//	frame = new Button("", nullptr, position, size, buttoncolor, SINGLECLICK, worldposition, this);
//
//	current = 0;
//	getinput = false;
//}
//
//InputBox::~InputBox()
//{
//	if (text)
//		game->textures->Unload(text);
//
//	delete frame;
//}
//
//elementstate InputBox::Update(float dt)
//{
//	if (game->input->GetButton(1) == DOWN && frame->state == NOTPRESSED)
//		getinput = false;
//
//	char textinput;
//	if (getinput && game->input->GetTextInput(textinput))
//	{
//		if (content == "" && textinput == ' ') {}
//		else
//		{
//			string::iterator itr = content.begin() + current;
//			content.insert(itr, textinput);
//			current++;
//		}
//	}
//	else if (game->input->GetKey(SDL_SCANCODE_LEFT) == DOWN)
//	{
//		if (current != 0)
//			current--;
//	}
//	else if (game->input->GetKey(SDL_SCANCODE_RIGHT) == DOWN)
//	{
//		if (current != content.size())
//			current++;
//	}
//	else if (game->input->GetKey(SDL_SCANCODE_BACKSPACE) == DOWN)
//	{
//		if (current != 0)
//		{
//			string::iterator itr = content.begin() + current - 1;
//			content.erase(itr);
//			current--;
//		}
//	}
//	else if (game->input->GetKey(SDL_SCANCODE_RETURN) == DOWN)
//	{
//		if (getinput && content != "")
//			observer.UIEvent(this);
//	}
//
//	if (text)
//		game->textures->Unload(text);
//
//	if (content != "")
//	{
//		string buffer = content;
//		if (getinput)
//		{
//			string::iterator itr = buffer.begin() + current;
//			buffer.insert(itr, '|');
//		}
//		text = game->textures->LoadText(font, buffer.c_str(), { 0,0,0,255 });
//
//		ipoint p = { 0,0 };
//		ipoint s = text->GetSize();
//		if (s.x > size.x)
//		{
//			s.x = size.x;
//			if (getinput)
//				p.x = text->GetSize().x - size.x;
//		}
//
//		game->render->RenderTexture(21, text, position, p.x, p.y, s, false, 255, worldposition);
//	}
//
//	return OK;
//}
//
//bool InputBox::CleanUp()
//{
//	return true;
//}
//
//void InputBox::UIEvent(UIElement* element)
//{
//	if (element == frame)
//		getinput = true;
//}
//
//string InputBox::GetContent()
//{
//	string output = content;
//
//	content.erase(content.begin(), content.end());
//	current = 0;
//
//	return output;
//}

#define IBOX_DEFAULT_SIZE_X 700
#define IBOX_DEFAULT_SIZE_Y 100

InputBox::InputBox(Font* font, const Color& fontcolor, const fpoint& position, Texture* texture, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, texture, worldposition, observer), text(nullptr), content(""), current(0), lastrendered(content)
{
	frame = new Button("", font, fontcolor, position, texture, Button::Type::LOCKONCLICK, worldposition, this);
	if (!texture)
		frame->SetSize(ipoint(IBOX_DEFAULT_SIZE_X, IBOX_DEFAULT_SIZE_Y));

	SetSize(frame->GetSize());

	PositionChanged();
}

InputBox::~InputBox()
{
	if (texture)
		game->textures->Unload(texture);

	delete frame;
}

UIElement::Output InputBox::Update(float dt)
{
	if (frame->IsLocked())
	{
		char textinput;
		if (game->input->GetTextInput(textinput))
		{
			string::iterator itr = content.begin() + current;
			content.insert(itr, textinput);
			current++;
		}
		else if (current != 0 && game->input->CheckState(Key::LEFT) == Input::State::DOWN)
			current--;
		else if (current != content.size() && game->input->CheckState(Key::RIGHT) == Input::State::DOWN)
			current++;
		else if (current != 0 && game->input->CheckState(Key::BACKSPACE) == Input::State::DOWN)
		{
			string::iterator itr = content.begin() + current - 1;
			content.erase(itr);
			current--;
		}
		else if (game->input->CheckState(Key::RETURN) == Input::State::DOWN || game->input->CheckState(Key::MOUSE_LEFT) == Input::State::DOWN)
		{
			if (content != "")
				observer.UIEvent(this);
			frame->Lock(false);
		}
	}

	return UIElement::Output::NO_MODIFY;
}

void InputBox::Render()
{
	if (content.size() > 0)
	{
		string buffer = content;
		if (frame->IsLocked())
		{
			string::iterator itr = buffer.begin() + current;
			buffer.insert(itr, '|');
		}

		if (buffer.compare(lastrendered)) // if they are different
		{
			if (text)
				game->textures->Unload(text);
			text = game->textures->LoadText(frame->GetFont(), buffer.c_str(), frame->GetColor());
			lastrendered = buffer;
		}

		ipoint textposition = { 0,0 };
		ipoint textsize = text->GetSize();
		ipoint size = ipoint(game->ResizeIPoint(GetSize(), 0.9f).x, GetSize().y);

		if (textsize.x > size.x)
		{
			textsize.x = size.x;
			if (frame->IsLocked())
				textposition.x = text->GetSize().x - size.x;
		}

		fpoint renderposition = game->Center(text->GetSize(), GetPosition(), GetSize(), GetPosition(), false, true);
		renderposition.x += (float)GetSize().x * 0.05f;
		game->render->RenderTexture(21, text, renderposition, textposition.x, textposition.y, textsize, false, 255, IsWorldPos());
	}
}

void InputBox::UIEvent(UIElement*)
{
}

const string InputBox::GetContent(bool dispose)
{
	const string output = content;
	if (dispose)
	{
		content.clear();
		current = 0;
	}
	return output;
}

void InputBox::ActiveChanged()
{
	frame->SetActive(IsActive());
}

void InputBox::PositionChanged()
{
	frame->SetPosition(GetPosition());
}

void InputBox::SizeChanged()
{
}

void InputBox::WorldPosChanged()
{
}
