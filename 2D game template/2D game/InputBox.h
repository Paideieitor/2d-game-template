#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include "UIElement.h"

class Label;
class Button;

class InputBox : public UIElement
{
private:

	InputBox() = delete;
	InputBox(const int id, const fpoint& position,
		bool worldposition = false, const Observer& observer = Observer());
	~InputBox();

	void Start(FontPtr font, const Color& fontcolor, const UIGraphics& graphics);
	bool Update(float dt) override;
	void Render() override;

public:

	void UIEvent(UIElement*) override;

	const std::string GetContent(bool dispose = true);
	void SetContent(const std::string& content);

private:

	void ActiveChanged() override;
	void DisableChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

private:

	std::string content;
	int current;

	std::string lastrendered;
	TexturePtr text;

	Button* frame = nullptr;

	friend class UIManager;
};

#endif
