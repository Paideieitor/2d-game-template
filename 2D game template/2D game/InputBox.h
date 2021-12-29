#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "UIElement.h"

class Font;

class Label;
class Button;

class InputBox : public UIElement
{
public:

	InputBox() = delete;
	InputBox(Font* font, const Color& fontcolor, const fpoint& position, Texture* texture = nullptr, 
		bool worldposition = false, const Observer& observer = Observer());
	~InputBox();

	UIElement::Output Update(float dt) override;
	void Render() override;

	void UIEvent(UIElement*) override;

	const string GetContent(bool dispose = true);

private:

	void ActiveChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

private:

	string content;
	int current;

	string lastrendered;
	Texture* text;

	Button* frame;
};

#endif
