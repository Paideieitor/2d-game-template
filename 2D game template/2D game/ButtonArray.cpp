#include "ButtonArray.h"

#include "UIManager.h"
#include "Textures.h"
#include "Render.h"

#include "Label.h"
#include "Button.h"

ButtonArray::ButtonArray(const std::string& text, FontPtr font, const Color& fontcolor, const std::vector<std::string>& options, const fpoint& position,
	TexturePtr texture, const UIStateTextures& maintextures, const UIStateTextures& unfoldtextures, bool worldposition, const Observer& observer)
	: UIElement(UIElement::Type::BUTTON, position, worldposition, observer), texture(texture), unfoldtextures(unfoldtextures), 
	options(options), change("")
{
	if (options.size() <= 0)
		delete this;

	if (text.size() > 0)
		this->text = new Label(text, font, fontcolor, position, worldposition);
	current = new Button(options[0], font, fontcolor, position, maintextures, Button::Type::LOCKONCLICK, worldposition, this);

	if (texture)
		textsize = texture->GetSize();
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
	if (!texture)
		game->render->RenderRectangle(UI_RENDER_LAYER, GetPosition(), textsize, Color(255, 50, 50), IsWorldPos());
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
		buttons.push_back(new Button(options[i], current->GetFont(), current->GetColor(), fpoint(0, 0), unfoldtextures, 
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
