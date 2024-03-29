#include "Label.h"

#include "Textures.h"
#include "Render.h"

Label::Label(const int id, const std::string& text, FontPtr font, const Color& color, const fpoint& position, bool worldposition)
	: UIElement(id, UIElement::Type::LABEL, position, worldposition, Observer()), text(text), font(font), color(color)
{
	ChangeText(text, font, color);
}

Label::~Label()
{
}

bool Label::Update(float dt)
{
	return true;
}

void Label::Render()
{
	if (texture)
	{
		int alpha = IsDisabled() ? 150 : 255;

		game->render->RenderTexture(true, UI_RENDER_LAYER, texture, GetPosition(), 0, 0, texture->GetSize(), false, alpha, IsWorldPos());
	}
}

void Label::ChangeText(const std::string& text, FontPtr font, const Color& color)
{
	this->text = text;
	if (font)
		this->font = font;
	if (color != Color::null)
		this->color = color;

	if (text.size() > 0)
	{
		texture = game->textures->LoadText(this->font, this->text.c_str(), this->color);
		if (texture)
			SetSize(texture->GetSize());
	}
}

void Label::ChangeFont(FontPtr font, const Color& color)
{
	ChangeText(text, font, color);
}

void Label::ChangeColor(const Color& color)
{
	ChangeText(text, font, color);
}
