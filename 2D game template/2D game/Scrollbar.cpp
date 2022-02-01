#include "Scrollbar.h"

#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "UIManager.h"

#define SBAR_DEFAULT_SIZE_X 500
#define SBAR_DEFAULT_SIZE_Y 20

Scrollbar::Scrollbar(const fpoint& position, Scrollbar::Type datatype, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::SCROLLBAR, position, worldposition, observer), datatype(datatype), value(0.0f)
{
}

Scrollbar::~Scrollbar()
{
	game->ui->EraseElement(bar);
	game->ui->EraseElement(scroll);

	game->ui->EraseElement(text);
	game->ui->EraseElement(valuetext);
}

void Scrollbar::Start(const std::string& text, FontPtr font, const Color& fontcolor, const UIGraphics& scrollgraphics, const UIGraphics& bargraphics)
{
	bar = game->ui->AddButton("", nullptr, Color::black, GetPosition(), scrollgraphics, Button::Type::REPEATPRESS, IsWorldPos(), this);
	scroll = game->ui->AddButton("", nullptr, Color::black, GetPosition(), bargraphics, Button::Type::REPEATPRESS, IsWorldPos(), this);

	this->text = game->ui->AddLabel(text, font, fontcolor, GetPosition(), IsWorldPos());
	valuetext = game->ui->AddLabel("0", font, fontcolor, GetPosition(), IsWorldPos());

	if (!bargraphics.texture)
		bar->SetSize(ipoint(SBAR_DEFAULT_SIZE_X, (int)((float)SBAR_DEFAULT_SIZE_Y * 0.75f)));
	if (!scrollgraphics.texture)
		scroll->SetSize(ipoint((int)((float)SBAR_DEFAULT_SIZE_X * 0.05f), SBAR_DEFAULT_SIZE_Y));
	SetSize(bar->GetSize().x, scroll->GetSize().y);

	PositionChanged();
}

bool Scrollbar::Update(float dt)
{
	if (bar->IsHovered() || scroll->IsHovered())
		if (game->input->CheckState(Key::MOUSE_SCROLL) == Input::State::UP)
		{
			++value;
			if (value > max)
				value = max;
			SetValue(value);

			SetScrollPositionFromValue();

			observer.UIEvent(this);
		}
		else if (game->input->CheckState(Key::MOUSE_SCROLL) == Input::State::DOWN)
		{
			--value;
			if (value < min)
				value = min;
			SetValue(value);

			SetScrollPositionFromValue();

			observer.UIEvent(this);
		}

	return true;
}

void Scrollbar::Render()
{
}

void Scrollbar::UIEvent(UIElement* element)
{
	float mouseposx = game->input->GetMousePos(IsWorldPos()).x + (float)game->render->GetCameraPosition().x;
	if (mouseposx < GetPosition().x)
		mouseposx = GetPosition().x;
	else if (mouseposx > GetPosition().x + (float)GetSize().x)
		mouseposx = GetPosition().x + (float)GetSize().x;

	float newvalue = min + ((mouseposx - GetPosition().x) / (float)GetSize().x) * Range();
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

void Scrollbar::SetMinMax(float min, float max)
{
	this->min = min;
	this->max = max;
}

void Scrollbar::ActiveChanged()
{
	bar->SetActive(IsActive());
	scroll->SetActive(IsActive());

	text->SetActive(IsActive());
	valuetext->SetActive(IsActive());
}

void Scrollbar::DisableChanged()
{
	bar->Disable(IsDisabled());
	scroll->Disable(IsDisabled());

	text->Disable(IsDisabled());
	valuetext->Disable(IsDisabled());
}

void Scrollbar::PositionChanged()
{
	fpoint position = GetPosition();
	bar->SetPosition(position.x, game->Center(bar->GetSize(), position, GetSize(), fpoint(0, 0), false, true).y);
	scroll->SetPosition(position.x + (GetSize().x * (1 / Range()) * value) - scroll->GetSize().x * 0.5f, position.y);

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
	float positionx = GetPosition().x + ((float)GetSize().x * (1 / Range()) * (value - min)) - scroll->GetSize().x * 0.5f;
	scroll->SetPosition(positionx, scroll->GetPosition().y);
}
