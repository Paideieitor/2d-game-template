#include "ButtonArray.h"

#include "UIManager.h"
#include "Textures.h"
#include "Render.h"

#include "Label.h"
#include "Button.h"

ButtonArray::ButtonArray(const std::string& text, FontPtr font, const Color& fontcolor, const std::vector<std::string>& options, const fpoint& position,
	const UIGraphics& graphics, const UIGraphics& togglegraphics, const UIGraphics& unfoldgraphics, bool worldposition, 
	const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, worldposition, observer), graphics(graphics), unfoldgraphics(unfoldgraphics),
	options(options), change("")
{
	if (text.size() > 0)
		this->text = new Label(text, font, fontcolor, position, worldposition);
	current = new Button(options[0], font, fontcolor, position, togglegraphics, Button::Type::LOCKONCLICK, worldposition, this);

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

ButtonArray::~ButtonArray()
{
	delete text;
	delete current;

	DeleteButtons();
}

UIElement::Output ButtonArray::Update(float dt)
{
	if (change.size() > 0)
	{
		current->ChangeText(change);
		change = "";

		DeleteButtons();
		current->Lock(false);
		observer.UIEvent(this);

		return UIElement::Output::LIST_MODIFY;
	}

	return UIElement::Output::NO_MODIFY;
}

void ButtonArray::Render()
{
	int alpha = IsDisabled() ? 50 : 255;

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
		buttons.push_back(new Button(options[i], current->GetFont(), current->GetColor(), fpoint(0, 0), unfoldgraphics, 
			Button::Type::SINGLECLICK, IsWorldPos(), this));
	PlaceButtons();
}

void ButtonArray::DeleteButtons()
{
	for (size_t i = 0; i < buttons.size(); ++i)
		delete buttons[i];
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
