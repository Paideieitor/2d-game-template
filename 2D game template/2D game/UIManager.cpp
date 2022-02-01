#include "UIManager.h"
#include "UIElement.h"

#include "Render.h"
#include "Window.h"
#include "Input.h"
#include "SceneManager.h"

UIManager::UIManager()
{
	name = "uimanager";
}

UIManager::~UIManager()
{

}

bool UIManager::SetUp(pugi::xml_node&)
{
	return true;
}

bool UIManager::Start()
{
	return true;
}

bool UIManager::Update(float dt)
{
	UIElement* focused = nullptr;

	std::vector<int> deleteindex;

	for (size_t i = 0; i < elements.size(); ++i)
	{
		if (!elements[i].first)
		{
			deleteindex.push_back(i);
			continue;
		}

		UIElement* element = elements[i].second;
		if (!element->IsActive())
			continue;

		if (!element->IsDisabled())
			if (element->Update(dt))
			{
				element->SetIdle();
				if (IsFocused(element))
					focused = element;
			}

		element->Render();
	}

	for (int i = deleteindex.size() - 1; i >= 0; --i)
	{
		delete elements[deleteindex[i]].second;
		elements.erase(elements.begin() + deleteindex[i]);
	}

	for (size_t i = 0; i < addelems.size(); ++i)
		elements.push_back(std::make_pair(true, addelems[i]));
	addelems.clear();

	if (focused)
	{
		if (game->input->CheckState(Key::MOUSE_LEFT) == Input::State::DOWN)
			focused->SetClicked();
		else
			focused->SetHover();
	}

	return true;
}

bool UIManager::CleanUp()
{
	while (elements.size() != 0)
	{
		if (elements.begin()->first)
			delete elements.begin()->second;
		elements.erase(elements.begin());
	}

	while (addelems.size() != 0)
	{
		delete *addelems.begin();
		addelems.erase(addelems.begin());
	}

	return true;
}

Button* UIManager::AddButton(const std::string& text, FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& graphics, Button::Type presstype, bool worldposition, const Observer& observer)
{
	Button* output = new Button(position, graphics, presstype, worldposition, observer);
	addelems.push_back(output);

	output->Start(text, font, fontcolor);

	return output;
}

ButtonArray* UIManager::AddButtonArray(const std::string& text, FontPtr font, const Color& fontcolor, const std::vector<std::string>& options, const fpoint& position, const UIGraphics& graphics, const UIGraphics& togglegraphics, const UIGraphics& unfoldgraphics, bool worldposition, const Observer& observer)
{
	ButtonArray* output = new ButtonArray(options, position, graphics, unfoldgraphics, worldposition, observer);
	addelems.push_back(output);

	output->Start(text, font, fontcolor, togglegraphics);

	return output;
}

InputBox* UIManager::AddInputBox(FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& graphics, bool worldposition, const Observer& observer)
{
	InputBox* output = new InputBox(position, worldposition, observer);
	addelems.push_back(output);

	output->Start(font, fontcolor, graphics);

	return output;
}

Label* UIManager::AddLabel(const std::string& text, FontPtr font, const Color& color, const fpoint& position, bool worldposition)
{
	Label* output = new Label(text, font, color, position, worldposition);
	addelems.push_back(output);

	return output;
}

Scrollbar* UIManager::AddScrollbar(const std::string& text, FontPtr font, const Color& fontcolor, const fpoint& position, const UIGraphics& scrollgraphics, const UIGraphics& bargraphics, Scrollbar::Type datatype, bool worldposition, const Observer& observer)
{
	Scrollbar* output = new Scrollbar(position, datatype, worldposition, observer);
	addelems.push_back(output);

	output->Start(text, font, fontcolor, scrollgraphics, bargraphics);

	return output;
}

void UIManager::EraseElement(UIElement* element)
{
	for (size_t i = 0; i < elements.size(); ++i)
		if (element == elements[i].second)
		{
			elements[i].first = false;
			element = nullptr;
			break;
		}
}

void UIManager::DisableAll()
{
	for (size_t i = 0; i < elements.size(); ++i)
		if (elements[i].first)
		{
			elements[i].second->SetIdle();
			elements[i].second->Disable(true);
		}
}

void UIManager::EnableAll()
{
	for (size_t i = 0; i < elements.size(); ++i)
		if (elements[i].first)
			elements[i].second->Disable(false);
}

bool UIManager::IsFocused(UIElement* element)
{
	if (element->type != UIElement::Type::BUTTON)
		return false;

	fpoint mousepos = game->input->GetMousePos(element->IsWorldPos());
	ipoint camera = game->render->GetCameraPosition(element->IsWorldPos());

	fpoint eposition = element->GetPosition();
	ipoint esize = element->GetSize();
	if (eposition.x < camera.x + mousepos.x && camera.x + mousepos.x < eposition.x + esize.x &&
		eposition.y < camera.y + mousepos.y && camera.y + mousepos.y < eposition.y + esize.y)
		return true;

	return false;
}
