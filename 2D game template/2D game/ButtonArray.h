#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include "UIElement.h"

class Label;
class Button;

class ButtonArray : public UIElement
{
public:

	ButtonArray() = delete;
	ButtonArray(const std::string& text, FontPtr font, const Color& fontcolor, const std::vector<std::string>& options, const fpoint& position, 
		TexturePtr texture = nullptr, const UIStateTextures& maintextures = UIStateTextures(), 
		const UIStateTextures& unfoldtextures = UIStateTextures(), bool worldposition = false, const Observer& observer = Observer());
	~ButtonArray();

	UIElement::Output Update(float dt) override;
	void Render() override;

	void UIEvent(UIElement*) override;

	const std::string GetCurrent() const;
	void SetCurrent(unsigned int index);
	void SetCurrent(const std::string& str);

private:

	void ActiveChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

	void CreateButtons();
	void DeleteButtons();
	void PlaceButtons();

private:

	TexturePtr texture;
	UIStateTextures unfoldtextures;

	Label* text;
	ipoint textsize; // size of the non-clickable part

	Button* current;

	std::vector<std::string> options;
	std::vector<Button*> buttons;

	std::string change;
};

#endif
