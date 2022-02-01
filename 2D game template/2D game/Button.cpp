#include "Button.h"

#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "UIManager.h"

Button::Button(const fpoint& position, const UIGraphics& graphics,
	Button::Type presstype, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, worldposition, observer), presstype(presstype), label(nullptr), locked(false), repeat(false), 
	graphics(graphics), current(graphics.idle)
{
}

Button::~Button()
{
	if (label)
		game->ui->EraseElement(label);
}

void Button::Start(const std::string& text, FontPtr font, const Color& fontcolor)
{
	label = game->ui->AddLabel(text, font, fontcolor, GetPosition(), IsWorldPos());

	ipoint size;
	if (current)
		size = current->GetCurrentSize();
	else if (label)
		size = game->ResizeIPoint(label->GetSize(), RECT_SIZE_MULTIPLIER);

	center.x = GetPosition().x + ((float)GetSize().x / 2.0f);
	center.y = GetPosition().y + ((float)GetSize().y / 2.0f);
	SetSize(size);
}

bool Button::Update(float dt)
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
		current = graphics.idle;
		break;
	case UIElement::State::HOVER:
		color.r -= 100;
		current = graphics.hover;
		break;
	case UIElement::State::CLICK:
		color.b += 100;
		current = graphics.click;
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
	}

	if (locked)
	{
		color = Color::blue;
		current = graphics.hover;
	}

	return true;
}

void Button::Render()
{
	if (current)
	{
		if (IsDisabled())
			current = graphics.disabled;
		game->render->RenderTexture(UI_RENDER_LAYER, graphics.texture, GetPosition(), current->GetFrame());
		SetSize(current->GetCurrentSize());
	}
	else
	{
		if (IsDisabled())
			color.a = 150;
		game->render->RenderRectangle(UI_RENDER_LAYER, GetPosition(), GetSize(), color, IsWorldPos());
	}
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

void Button::DisableChanged()
{
	label->Disable(IsDisabled());
}

void Button::PositionChanged()
{
	center.x = GetPosition().x + ((float)GetSize().x / 2.0f);
	center.y = GetPosition().y + ((float)GetSize().y / 2.0f);

	CenterLabel();
}

void Button::SizeChanged()
{
	fpoint position;
	position.x = center.x - ((float)GetSize().x / 2.0f);
	position.y = center.y - ((float)GetSize().y / 2.0f);
	SetPosition(position);
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
