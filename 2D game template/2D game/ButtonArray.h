#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include "UIElement.h"

class Label;
class Button;

class ButtonArray : public UIElement
{
private:

	ButtonArray() = delete;
	ButtonArray(const int id, const std::vector<std::string>& options, const fpoint& position,
		const UIGraphics& graphics = UIGraphics(),
		const UIGraphics& unfoldgraphics = UIGraphics(), bool worldposition = false, const Observer& observer = Observer());
	~ButtonArray();

	void Start(const std::string& text, FontPtr font, const Color& fontcolor, const UIGraphics& togglegraphics);
	bool Update(float dt) override;
	void Render() override;

public:

	void UIEvent(UIElement*) override;

	const std::string GetCurrent() const;
	void SetCurrent(unsigned int index);
	void SetCurrent(const std::string& str);

	const int GetIndex() const;

private:

	void ActiveChanged() override;
	void DisableChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

	void CreateButtons();
	void DeleteButtons();
	void PlaceButtons();

private:

	UIGraphics graphics;
	UIGraphics unfoldgraphics;

	Label* text = nullptr;
	ipoint textsize; // size of the non-clickable part

	Button* current = nullptr;

	const std::vector<std::string> options;
	std::vector<Button*> buttons;

	std::string change;

	friend class UIManager;
};

#endif
