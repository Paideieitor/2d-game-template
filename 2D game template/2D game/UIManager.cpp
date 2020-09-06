#include "UIManager.h"
#include "UIElements.h"

#include "Render.h"
#include "Window.h"
#include "Input.h"

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
	fpoint mousepos;
	ipoint camera = { 0, 0 };
	bool found = false;

	if (game->input->GetKey(SDL_SCANCODE_Q) == DOWN)
	{
		int a = 0;
	}

	if(elements.size() != 0)
		for (int e = elements.size() - 1; e > -1; e--)
		{
			UIElement* element = *(elements.begin() + e);

			mousepos = game->input->GetMousePos(element->worldposition);
			camera = { 0, 0 };
			if (element->worldposition)
			{
				camera = { -game->render->camera.x, -game->render->camera.y };
				camera /= game->window->scale;
			}

			if (!found && element->position.x < camera.x + mousepos.x && camera.x + mousepos.x < element->position.x + element->size.x &&
				element->position.y < camera.y + mousepos.y && camera.y + mousepos.y < element->position.y + element->size.y)
			{
				element->clickable = true;
				found = true;
			}
			else
			{
				element->clickable = false;
			}
		}

	int counter = 0;
	bool stop = true;
	while (stop)
	{
		stop = false;
		for (vector<UIElement*>::iterator e = elements.begin() + counter; e != elements.end(); e++)
		{
			UIElement* element = *e;

			switch (element->Update(dt))
			{
			case OK:
				break;
			case ERROR:
				cout << "UIManager Update -> Bad Thing, Error in " << element->name << endl;
				return false;
			case CHILD_CREATION:
				stop = true;
				break;
			case CHILD_DESTRUCTION:
				stop = true;
				break;
			}
			counter++;

			if (stop)
				break;
			if (game->scenes->changing)
			{
				stop = false;
				break;
			}
		}
	}

	return true;
}

bool UIManager::CleanUp()
{
	while (elements.size() != 0)
		delete *elements.begin();

	return true;
}

void UIManager::DestroyElement(UIElement* element)
{
	for (vector<UIElement*>::iterator e = elements.begin(); e != elements.end(); e++)
		if (element == *e)
		{
			delete *e;
			elements.erase(e);
			break;
		}
}

void UIManager::EraseElement(UIElement* element)
{
	for (vector<UIElement*>::iterator e = elements.begin(); e != elements.end(); e++)
		if (element == *e)
		{
			elements.erase(e);
			break;
		}
}