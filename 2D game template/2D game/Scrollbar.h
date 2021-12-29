#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "UIElement.h"

class Font;

class Label;
class Button;

class Scrollbar : public UIElement
{
public:

	enum class Type
	{
		INT,
		FLOAT
	};

	Scrollbar() = delete;
	Scrollbar(const string& text, Font* font, const Color& fontcolor, const fpoint& position, Texture* texture = nullptr, 
		Scrollbar::Type datatype = Scrollbar::Type::FLOAT, bool worldposition = false, const Observer& observer = Observer());
	~Scrollbar();

	UIElement::Output Update(float dt) override;
	void Render() override;

	void UIEvent(UIElement*);

	const float GetValue() const { return value; };
	void SetValue(float value);

private:

	void ActiveChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

	void SetScrollPositionFromValue();

private:

	Scrollbar::Type datatype;

	Label* text;
	Label* valuetext;

	Button* scroll;
	Button* bar;

	float value;
};

#endif
