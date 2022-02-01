#include "ButtonArray.h"

#include "Textures.h"
#include "Render.h"
#include "UIManager.h"

ButtonArray::ButtonArray(const std::vector<std::string>& options, const fpoint& position,
	const UIGraphics& graphics, const UIGraphics& unfoldgraphics, bool worldposition, 
	const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, worldposition, observer), graphics(graphics), unfoldgraphics(unfoldgraphics),
	options(options), change("")
{
}

ButtonArray::~ButtonArray()
{
	game->ui->EraseElement(text);
	game->ui->EraseElement(current);

	DeleteButtons();
}

void ButtonArray::Start(const std::string& text, FontPtr font, const Color& fontcolor, const UIGraphics& togglegraphics)
{
	if (text.size() > 0)
		this->text = game->ui->AddLabel(text, font, fontcolor, GetPosition(), IsWorldPos());
	current = game->ui->AddButton(options[0], font, fontcolor, GetPosition(), togglegraphics, Button::Type::LOCKONCLICK, IsWorldPos(), this);

	if (graphics.texture)
		textsize = graphics.texture->GetSize();
	else
		if (this->text)
			textsize = game->ResizeIPoint(this->text->GetSize(), RECT_SIZE_MULTIPLIER);
		else
			textsize = ipoint(0, 0);
	SetSize(textsize.x + current->GetSize().x, textsize.y);

	PositionChanged();
}

bool ButtonArray::Update(float dt)
{
	if (change.size() > 0)
	{
		current->ChangeText(change);
		change = "";

		DeleteButtons();
		current->Lock(false);
		observer.UIEvent(this);
	}

	return true;
}

void ButtonArray::Render()
{
	int alpha = IsDisabled() ? 150 : 255;

	if (!graphics.texture)
		game->render->RenderRectangle(UI_RENDER_LAYER, GetPosition(), textsize, Color(255, 50, 50, alpha), IsWorldPos());
	else
	{
		Animation animation = IsDisabled() ? graphics.disabled : graphics.idle;
		game->render->RenderTexture(UI_RENDER_LAYER, graphics.texture, GetPosition(), animation->GetFrame(), false, alpha, IsWorldPos());
	}
}

void ButtonArray::UIEvent(UIElement* element)
{
	if (element == current)
	{
		if (buttons.size() > 0)
			DeleteButtons();
		else
			CreateButtons();
	}
	else
		change = ((Button*)element)->GetText();
}

const std::string ButtonArray::GetCurrent() const
{
	return current->GetText();
}

void ButtonArray::SetCurrent(unsigned int index)
{
	if (index < options.size())
		current->ChangeText(options[index]);
}

void ButtonArray::SetCurrent(const std::string& str)
{
	current->ChangeText(str);
}

const int ButtonArray::GetIndex() const
{
	for (size_t i = 0; i < options.size(); ++i)
		if (options[i] == current->GetText())
			return i;
	return -1;
}

void ButtonArray::ActiveChanged()
{
	text->SetActive(IsActive());
	current->SetActive(IsActive());

	for (size_t i = 0; i < buttons.size(); ++i)
		buttons[i]->SetActive(IsActive());
}

void ButtonArray::DisableChanged()
{
	text->Disable(IsDisabled());
	current->Disable(IsDisabled());

	for (size_t i = 0; i < buttons.size(); ++i)
		buttons[i]->Disable(IsDisabled());
}

void ButtonArray::PositionChanged()
{
	fpoint position = GetPosition();

	text->SetPosition(game->Center(text->GetSize(), position, textsize));
	current->SetPosition(position.x + textsize.x, position.y);

	PlaceButtons();
}

void ButtonArray::SizeChanged()
{
}

void ButtonArray::WorldPosChanged()
{
	text->EnableWorldPos(IsWorldPos());
	current->EnableWorldPos(IsWorldPos());

	for (size_t i = 0; i < buttons.size(); ++i)
		buttons[i]->EnableWorldPos(IsWorldPos());
}

void ButtonArray::CreateButtons()
{
	for (size_t i = 0; i < options.size(); ++i)
		buttons.push_back(game->ui->AddButton(options[i], current->GetFont(), current->GetColor(), fpoint(0, 0), unfoldgraphics, 
			Button::Type::SINGLECLICK, IsWorldPos(), this));
	PlaceButtons();
}

void ButtonArray::DeleteButtons()
{
	for (size_t i = 0; i < buttons.size(); ++i)
		game->ui->EraseElement(buttons[i]);
	buttons.clear();
}

void ButtonArray::PlaceButtons()
{
	fpoint position = current->GetPosition();

	float positiony = position.y + (float)current->GetSize().y;
	for (size_t i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->SetPosition(position.x, positiony);
		positiony += (float)buttons[i]->GetSize().y;
	}
}
