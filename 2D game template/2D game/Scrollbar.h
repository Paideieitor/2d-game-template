#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "UIElement.h"

class Label;
class Button;
class InputBox;

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
	Scrollbar(const int id, const fpoint& position, Scrollbar::Type datatype = Scrollbar::Type::FLOAT, bool worldposition = false,
		const Observer& observer = Observer());
	~Scrollbar();

	void Start(const std::string& text, FontPtr font, const Color& fontcolor, const UIGraphics& scrollgraphics, const UIGraphics& bargraphics,
		const UIGraphics& valuegraphics);
	bool Update(float dt) override;
	void Render() override;

public:

	void UIEvent(UIElement*);

	const float GetValue() const { return value; };
	void SetValue(float value);

	const float GetMin() { return min; }
	const float GetMax() { return max; }
	void SetMinMax(float min, float max);

private:

	void ActiveChanged() override;
	void DisableChanged() override;
	void PositionChanged() override;
	void SizeChanged() override;
	void WorldPosChanged() override;

	void SetScrollPositionFromValue();

	float Range() { return max - min; }

private:

	Scrollbar::Type datatype;

	Label* text = nullptr;
	InputBox* valuetext = nullptr;

	Button* scroll = nullptr;
	Button* bar = nullptr;

	float value;

	float min = 0.0f;
	float max = 100.0f;

	friend class UIManager;
};

#endif
