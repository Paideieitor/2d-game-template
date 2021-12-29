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
	// -- Creates a button and adds it to the UI manager --
	// --- Parameters: ---
	// text -> text showcased at the center of the button
	// font -> font of the text
	// font color -> color of the text
	// position -> top left position of the button
	// textures -> textures to be used
	// press type -> defines the buttons behavior
	// world position -> defines if the button will be rendered on world coordinates or screen coordinates
	// observer -> structure that will receive the UIEvent call
	Button(const string& text, Font* font, const Color& fontcolor, const fpoint& position, const UIStateTextures& textures = UIStateTextures(), 
		Button::Type presstype = Button::Type::SINGLECLICK, bool worldposition = false, const Observer& observer = Observer());
	~Button();

	UIElement::Output Update(float dt) override;

	void Render() override;

	const bool IsLocked() const { return locked; }
	// This function does not trigger a UIEvent
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

	Label* label;

	Texture* idle;
	Texture* hover;
	Texture* click;
	Texture* disabled;
	Texture* current;

	Color color; // for when no texture
};

#endif
