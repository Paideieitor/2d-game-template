#include "Button.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"

#include "Label.h"

Button::Button(const std::string& text, FontPtr font, const Color& fontcolor, const fpoint& position, const UIStateTextures& textures,
	Button::Type presstype, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, worldposition, observer), presstype(presstype), label(nullptr), locked(false), repeat(false), 
	idle(textures.GetTexture(UIElement::State::IDLE)), hover(textures.GetTexture(UIElement::State::HOVER)), 
	click(textures.GetTexture(UIElement::State::CLICK)), disabled(textures.GetTexture(UIElement::State::DISABLED)), 
	current(idle)
{
	label = new Label(text, font, fontcolor, position, worldposition);
	if (current)
		SetSize(current->GetSize());
	else if (label)
		SetSize(game->ResizeIPoint(label->GetSize(), RECT_SIZE_MULTIPLIER));

	CenterLabel();
}

Button::~Button()
{
	if (label)
		delete label;
}

UIElement::Output Button::Update(float dt)
{
	if (repeat)
		if (game->input->CheckState(Key::MOUSE_LEFT) == Input::State::UP)
			repeat = false;
		else
			SetClicked();

	color = Color::red;
	switch (state)
	{
	case UIElement::State::IDLE:
		current = idle;
		break;
	case UIElement::State::HOVER:
		color.r -= 100;
		current = hover;
		break;
	case UIElement::State::CLICK:
		color.b += 100;
		current = click;
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
		current = disabled;
		break;
	}

	if (locked)
	{
		color = Color::blue;
		current = hover;
	}

	return UIElement::Output::NO_MODIFY;
}

void Button::Render()
{
	if (current)
		game->render->RenderTexture(UI_RENDER_LAYER, current, GetPosition(), 0, 0, current->GetSize());
	else
		game->render->RenderRectangle(UI_RENDER_LAYER, GetPosition(), GetSize(), color, IsWorldPos());
}

const std::string Button::GetText() const
{
	return label ? label->GetText() : "";
}

FontPtr const Button::GetFont() const
{
	return label ? label->GetFont() : nullptr;
}

const Color Button::GetColor() const
{
	return label ? label->GetColor() : Color::black;
}

void Button::ChangeText(const std::string& text)
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
