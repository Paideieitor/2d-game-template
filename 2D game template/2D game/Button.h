#ifndef BUTTON_H
#define BUTTON_H

#include "UIElement.h"

#define RECT_SIZE_MULTIPLIER 1.5f

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
	Button(const std::string& text, FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& graphics = UIGraphics(),
		Button::Type presstype = Button::Type::SINGLECLICK, bool worldposition = false, const Observer& observer = Observer());
	~Button();

	bool Update(float dt) override;

	void Render() override;

	const bool IsLocked() const { return locked; }
	// This function does not trigger a UIEvent
	void Lock(bool enable) { locked = enable; }

	const std::string GetText() const;
	FontPtr const GetFont() const;
	const Color GetColor() const;

	void ChangeText(const std::string& text);

public:

	Button::Type presstype;

private:

	void ActiveChanged() override;
	void DisableChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

	void CenterLabel();

private:

	bool locked;
	bool repeat;

	Label* label;

	UIGraphics graphics;
	Animation current; // important current is declared after graphics

	Color color; // for when no texture

	fpoint center;
};

#endif
