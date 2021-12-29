#include "Label.h"

#include "Textures.h"
#include "Render.h"

Label::Label(const string& text, Font* font, const Color& color, const fpoint& position, bool worldposition)
	: UIElement(UIElement::Type::LABEL, position, worldposition, Observer()), text(text), font(font), color(color)
{
	ChangeText(text, font, color);
	if (texture)
		SetSize(texture->GetSize());
}

Label::~Label()
{
	if (texture)
		game->textures->Unload(texture);
}

UIElement::Output Label::Update(float dt)
{
	return Output::NO_MODIFY;
}

void Label::Render()
{
	if (texture)
	{
		ipoint rendersize = GetSize();
		if (rendersize.IsZero())
			rendersize = texture->GetSize();
		game->render->RenderTexture(UI_RENDER_LAYER, texture, GetPosition(), 0, 0, rendersize, false, 255, IsWorldPos());
	}
}

void Label::ChangeText(const string& text, Font* font, const Color& color)
{
	this->text = text;
	if (font)
		this->font = font;
	if (color != Color::null)
		this->color = color;

	if (texture)
		game->textures->Unload(texture);
	if (text.size() > 0)
	{
		texture = game->textures->LoadText(this->font, this->text.c_str(), this->color);
		if (texture)
			SetSize(texture->GetSize());
	}
}

void Label::ChangeFont(Font* font, const Color& color)
{
	ChangeText(text, font, color);
}

void Label::ChangeColor(const Color& color)
{
	ChangeText(text, font, color);
}
