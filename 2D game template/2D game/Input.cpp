#include "Input.h"

#include "Window.h"
#include "Render.h"

#include "SDL/include/SDL_events.h"

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
		keyboard[i] = State::IDLE;
	for (int i = 0; i < MAX_BUTTONS; i++)
		mousebuttons[i] = State::IDLE;
	mousescroll = State::IDLE;
	
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
			if (keyboard[i] == State::IDLE)
				keyboard[i] = State::DOWN;
			else if (keyboard[i] == State::DOWN)
				keyboard[i] = State::REPEAT;
		}
		else
		{
			if (keyboard[i] == State::REPEAT
				|| keyboard[i] == State::DOWN)
				keyboard[i] = State::UP;
			else if (keyboard[i] == State::UP)
				keyboard[i] = State::IDLE;
		}

	for (int i = 0; i < MAX_BUTTONS; i++)
		if (mousebuttons[i] == State::DOWN)
			mousebuttons[i] = State::REPEAT;
		else if (mousebuttons[i] == State::UP)
			mousebuttons[i] = State::IDLE;

	mousescroll = State::IDLE;

	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			game->window->SetState(Window::State::QUIT);
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				game->window->SetState(Window::State::HIDE);
				break;
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				game->window->SetState(Window::State::SHOW);
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mousebuttons[event.button.button - 1] = State::DOWN;
			break;
		case SDL_MOUSEBUTTONUP:
			mousebuttons[event.button.button - 1] = State::UP;
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				mousescroll = State::UP;
			else if (event.wheel.y < 0)
				mousescroll = State::DOWN;
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

const Input::State Input::CheckState(Key key) const
{
	if ((int)key < (int)Key::MOUSE_LEFT)
		return keyboard[(int)key];

	if ((int)Key::MOUSE_LEFT <= (int)key && (int)key < (int)Key::MOUSE_10)
		return mousebuttons[(int)key - (int)Key::MOUSE_LEFT];

	if ((int)Key::MOUSE_SCROLL)
		return mousescroll;

	return State::IDLE;
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

fpoint Input::GetMousePos(bool worldposition) const
{
	if (worldposition)
	{
		fpoint mousepos = (mouse / (fpoint)game->render->GetResolution(true)) * (fpoint)game->render->GetResolution(false);
		return  mousepos + (fpoint)game->render->GetCameraPosition();
	}

	return mouse;
}