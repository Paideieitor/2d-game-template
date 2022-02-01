#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "UIElement.h"

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

private:

	Scrollbar() = delete;
	Scrollbar(const fpoint& position, Scrollbar::Type datatype = Scrollbar::Type::FLOAT, bool worldposition = false, 
		const Observer& observer = Observer());
	~Scrollbar();

	void Start(const std::string& text, FontPtr font, const Color& fontcolor, const UIGraphics& scrollgraphics, const UIGraphics& bargraphics);
	bool Update(float dt) override;
	void Render() override;

public:

	void UIEvent(UIElement*);

	const float GetValue() const { return value; };
	void SetValue(float value);

private:

	void ActiveChanged() override;
	void DisableChanged() override;
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

	friend class UIManager;
};

#endif
