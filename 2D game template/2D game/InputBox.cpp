#include "InputBox.h"

#include "Input.h"
#include "Textures.h"
#include "Render.h"

#include "Label.h"
#include "Button.h"

#define IBOX_DEFAULT_SIZE_X 700
#define IBOX_DEFAULT_SIZE_Y 100

InputBox::InputBox(FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& graphics, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, worldposition, observer), text(nullptr), content(""), current(0), lastrendered(content)
{
	frame = new Button("", font, fontcolor, position, graphics, Button::Type::LOCKONCLICK, worldposition, this);
	if (!graphics.texture)
		frame->SetSize(ipoint(IBOX_DEFAULT_SIZE_X, IBOX_DEFAULT_SIZE_Y));

	SetSize(frame->GetSize());

	PositionChanged();
}

InputBox::~InputBox()
{
	delete frame;
}

bool InputBox::Update(float dt)
{
	if (frame->IsLocked())
	{
		char textinput;
		if (game->input->GetTextInput(textinput))
		{
			content.insert(content.begin() + current, textinput);
			current++;
		}
		else if (current != 0 && game->input->CheckState(Key::LEFT) == Input::State::DOWN)
			current--;
		else if (current != content.size() && game->input->CheckState(Key::RIGHT) == Input::State::DOWN)
			current++;
		else if (current != 0 && game->input->CheckState(Key::BACKSPACE) == Input::State::DOWN)
		{
			content.erase(content.begin() + current - 1);
			current--;
		}
		else if (game->input->CheckState(Key::RETURN) == Input::State::DOWN)
		{
			if (content != "")
				observer.UIEvent(this);
			frame->Lock(false);
		}
		else if (game->input->CheckState(Key::MOUSE_LEFT) == Input::State::DOWN)
			frame->Lock(false);
	}

	return true;
}

void InputBox::Render()
{
	if (content.size() > 0)
	{
		std::string buffer = content;
		if (frame->IsLocked())
			buffer.insert(buffer.begin() + current, '|');

		if (buffer.compare(lastrendered)) // if they are different
		{
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

		int alpha = IsDisabled() ? 150 : 255;
		game->render->RenderTexture(21, text, renderposition, textposition.x, textposition.y, textsize, false, alpha, IsWorldPos());
	}
}

void InputBox::UIEvent(UIElement*)
{
}

const std::string InputBox::GetContent(bool dispose)
{
	const std::string output = content;
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

void InputBox::DisableChanged()
{
	frame->Disable(IsDisabled());
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
	frame->EnableWorldPos(IsWorldPos());
}
