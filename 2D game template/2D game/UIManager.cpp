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

	int counter = 0;
	bool stop = false;
	while (!stop)
	{
		stop = true;
		listmodify = false;
		for (size_t i = counter; i < elements.size(); ++i)
		{
			counter++;

			if (!elements[i]->IsActive())
				continue;

			if (!elements[i]->IsDisabled())
			{
				if (elements[i]->Update(dt))
				{
					elements[i]->SetIdle();
					if (IsFocused(elements[i]))
						focused = elements[i];
				}

				if (listmodify)
				{
					stop = false;
					break;
				}
			}

			elements[i]->Render();

			if (!stop)
				break;
			if (game->scenes->ChangingScenes())
			{
				stop = true;
				break;
			}
		}
	}

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
		delete *elements.begin();

	return true;
}

void UIManager::DisableAll()
{
	for (size_t i = 0; i < elements.size(); ++i)
	{
		elements[i]->SetIdle();
		elements[i]->Disable(true);
	}
}

void UIManager::EnableAll()
{
	for (size_t i = 0; i < elements.size(); ++i)
		elements[i]->Disable(false);
}

void UIManager::AddElement(UIElement* element)
{
	game->ui->elements.push_back(element);
	listmodify = true;
}

void UIManager::EraseElement(UIElement* element)
{
	for (std::vector<UIElement*>::iterator e = elements.begin(); e != elements.end(); e++)
		if (element == *e)
		{
			elements.erase(e);
			listmodify = true;
			break;
		}
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
