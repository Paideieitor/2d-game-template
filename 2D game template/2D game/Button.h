#ifndef BUTTON_H
#define BUTTON_H

#include "UIElement.h"

#define RECT_SIZE_MULTIPLIER 1.5f

class Font;

class Label;

class Button : public UIElement
{
public:

	enum class Type
	{
		SINGLECLICK,
		LOCKONCLICK,
		REPEATPRESS
	};

	Button() = delete;
	Button(const string& text, Font* font, const Color& fontcolor, const fpoint& position, Texture* texture = nullptr, 
		Button::Type presstype = Button::Type::SINGLECLICK, bool worldposition = false, const Observer& observer = Observer());
	~Button();

	UIElement::Output Update(float dt) override;

	void Render() override;

	const bool IsLocked() const { return locked; }
	void Lock(bool enable) { locked = enable; }

	const string GetText() const;
	Font* const GetFont() const;
	const Color GetColor() const;

	void ChangeText(const string& text);

public:

	Button::Type presstype;

private:

	void ActiveChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

	void CenterLabel();

private:

	bool locked;
	bool repeat;

	Color color;

	Label* label;
};

#endif
