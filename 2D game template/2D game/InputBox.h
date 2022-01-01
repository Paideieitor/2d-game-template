#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "UIElement.h"

class Label;
class Button;

class InputBox : public UIElement
{
public:

	InputBox() = delete;
	InputBox(FontPtr font, const Color& fontcolor, const fpoint& position, const UIStateTextures& textures = UIStateTextures(),
		bool worldposition = false, const Observer& observer = Observer());
	~InputBox();

	UIElement::Output Update(float dt) override;
	void Render() override;

	void UIEvent(UIElement*) override;

	const std::string GetContent(bool dispose = true);

private:

	void ActiveChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

private:

	std::string content;
	int current;

	std::string lastrendered;
	TexturePtr text;

	Button* frame;
};

#endif
