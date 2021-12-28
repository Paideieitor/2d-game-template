#include "Button.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"

#include "Label.h"

Button::Button(const string& text, Font* font, const Color& fontcolor, const fpoint& position, Texture* texture, Button::Type presstype,
	bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, texture, worldposition, observer), presstype(presstype), label(nullptr), locked(false), repeat(false)
{
	if (text.size() > 0 && font)
	{
		label = new Label(text, font, fontcolor, position, worldposition);
		if (!texture)
			SetSize(game->ResizeIPoint(label->GetSize(), RECT_SIZE_MULTIPLIER));
	}

	CenterLabel();
}

Button::~Button()
{
	if (label)
		delete label;
}

UIElement::Output Button::Update(float dt)
{
	color = Color::red;

	if (repeat)
		if (game->input->GetButton(1) == keystate::UP)
			repeat = false;
		else
			SetClicked();

	switch (state)
	{
	case UIElement::State::IDLE:
		break;
	case UIElement::State::HOVER:
		color.r -= 100;
		break;
	case UIElement::State::CLICK:
		color.b += 100;
		switch (presstype)
		{
		case Button::Type::LOCKONCLICK:
			locked = !locked;
			break;
		case Button::Type::REPEATPRESS:
			repeat = true;
			break;
		}
		observer.UIEvent(this);
		break;
	case UIElement::State::DISABLED:
		break;
	}

	if (locked)
		color = Color::blue;// color.a -= 100;

	return UIElement::Output::NO_MODIFY;
}

void Button::Render()
{
	if (texture)
		game->render->RenderTexture(UI_RENDER_LAYER, texture, GetPosition(), 0, 0, GetSize(), false, color.a);
	else
		game->render->RenderRectangle(UI_RENDER_LAYER, GetPosition(), GetSize(), color, IsWorldPos());
}

const string Button::GetText() const
{
	return label ? label->GetText() : "";
}

Font* const Button::GetFont() const
{
	return label ? label->GetFont() : nullptr;
}

const Color Button::GetColor() const
{
	return label ? label->GetColor() : Color::black;
}

void Button::ChangeText(const string& text)
{
	if (label)
	{
		label->ChangeText(text);
		CenterLabel();
	}
}

void Button::ActiveChanged()
{
	label->SetActive(IsActive());
}

void Button::PositionChanged()
{
	CenterLabel();
}

void Button::SizeChanged()
{
	CenterLabel();
}

void Button::WorldPosChanged()
{
	label->EnableWorldPos(IsWorldPos());
}

void Button::CenterLabel()
{
	if (!label)
		return;

	label->SetPosition(game->Center(label->GetSize(), GetPosition(), GetSize()));
}
