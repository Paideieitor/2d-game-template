#include "Input.h"

#include "Window.h"

Input::Input()
{
	name = "input";
}

Input::~Input()
{

}

bool Input::SetUp(pugi::xml_node&)
{
	for (int i = 0; i < MAX_KEYS; i++)
		keyboard[i] = IDLE;
	for (int i = 0; i < MAX_BUTTONS; i++)
		mousebuttons[i] = IDLE;
	
	return true;
}

bool Input::Start()
{
	//SDL_StopTextInput();

	return true;
}

bool Input::Update(float dt)
{
	inputrecieved = false;
	textinput = ' ';

	SDL_Event event;
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; i++)
		if (keys[i] == 1)
		{
			if (keyboard[i] == IDLE)
				keyboard[i] = DOWN;
			else if (keyboard[i] == DOWN)
				keyboard[i] = REPEAT;
		}
		else
		{
			if (keyboard[i] == REPEAT 
				|| keyboard[i] == DOWN)
				keyboard[i] = UP;
			else if (keyboard[i] == UP)
				keyboard[i] = IDLE;
		}

	for (int i = 0; i < MAX_BUTTONS; i++)
		if (mousebuttons[i] == DOWN)
			mousebuttons[i] = REPEAT;
		else if (mousebuttons[i] == UP)
			mousebuttons[i] = IDLE;

	if (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			game->window->SetState(windowstate::QUIT);
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				game->window->SetState(windowstate::HIDE);
				break;
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				game->window->SetState(windowstate::SHOW);
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mousebuttons[event.button.button - 1] = DOWN;
			break;
		case SDL_MOUSEBUTTONUP:
			mousebuttons[event.button.button - 1] = UP;
			break;
		case SDL_MOUSEMOTION:
			mouse.x = (float)event.motion.x;
			mouse.y = (float)event.motion.y;
			break;
		case SDL_TEXTINPUT:
			inputrecieved = true;
			textinput = *event.text.text;
			break;
		}


	return true;
}

bool Input::CleanUp()
{
	//SDL_StartTextInput();

	return true;
}

keystate Input::GetKey(int key) const
{
	return keyboard[key];
}

keystate Input::GetButton(int button) const
{
	return mousebuttons[button - 1];
}

bool Input::GetTextInput(char& input)
{
	if (inputrecieved)
	{
		input = textinput;
		return true;
	}
	else
		return false;
}

fpoint Input::GetMousePos(bool usescale) const
{
	fpoint output;
	if (usescale)
		return mouse / game->window->GetScale();
	return mouse;
}