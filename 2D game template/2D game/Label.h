#ifndef LABEL_H
#define LABEL_H

#include "UIElement.h"

class Label : public UIElement
{
private:

	Label() = delete;
	Label(const std::string& text, FontPtr font, const Color& color, const fpoint& position, bool worldposition = false);
	~Label();

	bool Update(float dt) override;
	void Render() override;

public:

	const std::string GetText() const { return text; }
	FontPtr const GetFont() const { return font; }
	const Color GetColor() const { return color; }

	void ChangeText(const std::string& text, FontPtr font = nullptr, const Color& color = Color::null);
	void ChangeFont(FontPtr font, const Color& color = Color::black);
	void ChangeColor(const Color& color);

private:

	void ActiveChanged() override {}
	void DisableChanged() override {}
	void PositionChanged() override {}
	void SizeChanged() override {}
	void WorldPosChanged() override {}

private:

	std::string text;

	TexturePtr texture;
	FontPtr font;
	Color color;

	friend class UIManager;
};

#endif
