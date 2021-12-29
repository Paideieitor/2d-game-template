#include "Scrollbar.h"

#include "Render.h"
#include "Textures.h"
#include "Input.h"

#include "Label.h"
#include "Button.h"

#define SBAR_DEFAULT_SIZE_X 500
#define SBAR_DEFAULT_SIZE_Y 20

Scrollbar::Scrollbar(const string& text, Font* font, const Color& fontcolor, const fpoint& position, const UIStateTextures& scrolltextures,
	const UIStateTextures& bartextures, Scrollbar::Type datatype, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::SCROLLBAR, position, worldposition, observer), datatype(datatype), value(0.0f)
{
	bar = new Button("", nullptr, Color::black, position, bartextures, Button::Type::REPEATPRESS, worldposition, this);
	scroll = new Button("", nullptr, Color::black, position, scrolltextures, Button::Type::REPEATPRESS, worldposition, this);

	this->text = new Label(text, font, fontcolor, position, worldposition);
	valuetext = new Label("0", font, fontcolor, position, worldposition);

	if (!bartextures.GetTexture(UIElement::State::IDLE))
		bar->SetSize(ipoint(SBAR_DEFAULT_SIZE_X, (int)((float)SBAR_DEFAULT_SIZE_Y * 0.75f)));
	if (!scrolltextures.GetTexture(UIElement::State::IDLE))
		scroll->SetSize(ipoint((int)((float)SBAR_DEFAULT_SIZE_X * 0.05f), SBAR_DEFAULT_SIZE_Y));
	SetSize(bar->GetSize().x, scroll->GetSize().y);

	PositionChanged();
}

Scrollbar::~Scrollbar()
{
	delete bar;
	delete scroll;

	delete text;
	delete valuetext;
}

UIElement::Output Scrollbar::Update(float dt)
{
	if (bar->IsHovered() || scroll->IsHovered())
		if (game->input->CheckState(Key::MOUSE_SCROLL) == Input::State::UP)
		{
			++value;
			if (value > 100.0f)
				value = 100.0f;
			SetValue(value);

			SetScrollPositionFromValue();

			observer.UIEvent(this);
		}
		else if (game->input->CheckState(Key::MOUSE_SCROLL) == Input::State::DOWN)
		{
			--value;
			if (value < 0.0f)
				value = 0.0f;
			SetValue(value);

			SetScrollPositionFromValue();

			observer.UIEvent(this);
		}

	return UIElement::Output::NO_MODIFY;
}

void Scrollbar::Render()
{
}

void Scrollbar::UIEvent(UIElement* element)
{
	float mouseposx = game->input->GetMousePos(IsWorldPos()).x + (float)game->render->GetCameraPosition(IsWorldPos()).x;
	if (mouseposx < GetPosition().x)
		mouseposx = GetPosition().x;
	else if (mouseposx > GetPosition().x + (float)GetSize().x)
		mouseposx = GetPosition().x + (float)GetSize().x;

	float newvalue = ((mouseposx - GetPosition().x) / (float)GetSize().x) * 100.0f;
	if (newvalue != value)
	{
		SetValue(newvalue);
		observer.UIEvent(this);
	}
}

void Scrollbar::SetValue(float value)
{
	if (datatype == Scrollbar::Type::INT)
		value = (float)(int)value;

	this->value = value;
	SetScrollPositionFromValue();

	valuetext->ChangeText(game->FloatToString(value));
}

void Scrollbar::ActiveChanged()
{
	bar->SetActive(IsActive());
	scroll->SetActive(IsActive());

	text->SetActive(IsActive());
	valuetext->SetActive(IsActive());
}

void Scrollbar::PositionChanged()
{
	fpoint position = GetPosition();
	bar->SetPosition(position.x, game->Center(bar->GetSize(), position, GetSize(), fpoint(0, 0), false, true).y);
	scroll->SetPosition(position.x + (value * GetSize().x * 0.01f) - scroll->GetSize().x * 0.5f, position.y);

	text->SetPosition(position.x, position.y - text->GetSize().y);
	valuetext->SetPosition(position.x + GetSize().x + GetSize().x * 0.05f, game->Center(valuetext->GetSize(), position, GetSize()).y);
}

void Scrollbar::SizeChanged()
{
	ipoint size = GetSize();
	bar->SetSize(ipoint(size.x, (int)((float)size.y * 0.75f)));
	scroll->SetSize(ipoint((int)((float)size.x * 0.05f), size.y));

	PositionChanged();
}

void Scrollbar::WorldPosChanged()
{
	bar->EnableWorldPos(IsWorldPos());
	scroll->EnableWorldPos(IsWorldPos());

	text->EnableWorldPos(IsWorldPos());
	valuetext->EnableWorldPos(IsWorldPos());
}

void Scrollbar::SetScrollPositionFromValue()
{
	float positionx = GetPosition().x + ((float)GetSize().x * 0.01f * value) - scroll->GetSize().x * 0.5f;
	scroll->SetPosition(positionx, scroll->GetPosition().y);
}
