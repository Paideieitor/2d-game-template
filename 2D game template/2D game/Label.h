#ifndef LABEL_H
#define LABEL_H

#include "UIElement.h"

class Texture;
class Font;

class Label : public UIElement
{
public:

	Label() = delete;
	Label(const string& text, Font* font, const Color& color, const fpoint& position, bool worldposition = false);
	~Label();

	Output Update(float dt) override;
	void Render() override;

	const string GetText() const { return text; }
	Font* const GetFont() const { return font; }
	const Color GetColor() const { return color; }

	void ChangeText(const string& text, Font* font = nullptr, const Color& color = Color::null);
	void ChangeFont(Font* font, const Color& color = Color::black);
	void ChangeColor(const Color& color);

private:

	void ActiveChanged() override {}
	void PositionChanged() override {}
	void SizeChanged() override {}
	void WorldPosChanged() override {}

private:

	string text;

	Font* font;
	Color color;
};

#endif
