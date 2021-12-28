#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include "UIElement.h"

class Font;

class Label;
class Button;

class ButtonArray : public UIElement
{
public:

	ButtonArray() = delete;
	ButtonArray(const string& text, Font* font, const Color& fontcolor, const vector<string>& options, const fpoint& position, Texture* texture = nullptr,
		bool worldposition = false, const Observer& observer = Observer());
	~ButtonArray();

	UIElement::Output Update(float dt) override;
	void Render() override;

	void UIEvent(UIElement*) override;

	const string GetCurrent() const;

private:

	void ActiveChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

	void CreateButtons();
	void DeleteButtons();
	void PlaceButtons();

private:

	Label* text;
	ipoint textsize; // size of the non-clickable part

	Button* current;

	vector<string> options;
	vector<Button*> buttons;

	string change;
};

#endif
