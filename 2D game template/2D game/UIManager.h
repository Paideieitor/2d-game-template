#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Module.h"

class UIElement;

#include "Button.h"
#include "ButtonArray.h"
#include "InputBox.h"
#include "Label.h"
#include "Scrollbar.h"

class UIManager : public Module
{
public:

	UIManager();
	~UIManager();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	Button* AddButton(const std::string& text, FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& graphics = UIGraphics(),
		Button::Type presstype = Button::Type::SINGLECLICK, bool worldposition = false, const Observer& observer = Observer());
	ButtonArray* AddButtonArray(const std::string& text, FontPtr font, const Color& fontcolor, const std::vector<std::string>& options, const fpoint& position,
		const UIGraphics& graphics = UIGraphics(), const UIGraphics& togglegraphics = UIGraphics(),
		const UIGraphics& unfoldgraphics = UIGraphics(), bool worldposition = false, const Observer& observer = Observer());
	InputBox* AddInputBox(FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& graphics = UIGraphics(),
		bool worldposition = false, const Observer& observer = Observer());
	Label* AddLabel(const std::string& text, FontPtr font, const Color& color, const fpoint& position, bool worldposition = false);
	Scrollbar* AddScrollbar(const std::string& text, FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& scrollgraphics = UIGraphics(),
		const UIGraphics& bargraphics = UIGraphics(), Scrollbar::Type datatype = Scrollbar::Type::FLOAT, bool worldposition = false,
		const Observer& observer = Observer());

	void EraseElement(UIElement* element);

	void DisableAll();
	void EnableAll();

private:

	bool IsFocused(UIElement*);

private:

	std::vector<std::pair<bool, UIElement*>> elements;

	std::vector<UIElement*> addelems;

	friend class UIElement;
};

#endif