#include "Window.h"

#include "SDL/include/SDL_video.h"

Window::Window()
{
    name = "window";
}

Window::~Window()
{
    SDL_DestroyWindow(window);
}

bool Window::SetUp(pugi::xml_node& node)
{
    this->node = node;
    width = node.attribute("width").as_int();
    height = node.attribute("height").as_int();
    scale = node.attribute("scale").as_float();
    
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED;
    fullscreen = false;
    borderless = false;
    grabbed = true;

    if (node.child("fullscreen").attribute("value").as_bool() == true)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
        fullscreen = true;
    }
    if (node.child("borderless").attribute("value").as_bool() == true)
    {
        flags |= SDL_WINDOW_BORDERLESS;
        borderless = true;
    }

    window = SDL_CreateWindow("Archipielago", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

    if (window == NULL)
    {
        game->Log("Window -> Bad Thing, Error: " + std::string(SDL_GetError()));
        return false;
    }

	return true;
}

bool Window::Start()
{
    state = Window::State::SHOW;

	return true;
}

bool Window::Update(float dt)
{
    switch (state)
    {
    case Window::State::QUIT:
        return false;
        break;
    case Window::State::HIDE:
        break;
    case Window::State::SHOW:
        break;
    }

	return true;
}

bool Window::CleanUp()
{

	return true;
}

void Window::SetFullscreen(bool enable)
{
    SDL_WindowFlags flags = (SDL_WindowFlags)0;
    if (enable)
        flags = SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(window, flags);

    fullscreen = enable;
    node.child("fullscreen").attribute("value").set_value(fullscreen);
    game->document.save_file("config.xml");
}

void Window::SetBorderless(bool enable)
{
    SDL_SetWindowBordered(window, (SDL_bool)!enable);

    borderless = enable;
    node.child("borderless").attribute("value").set_value(borderless);
    game->document.save_file("config.xml");
}

void Window::SetGrabbed(bool enable)
{
    SDL_SetWindowGrab(window, (SDL_bool)enable);
    grabbed = enable;
}

void Window::SetWindowSize(ipoint size)
{
    SDL_SetWindowSize(window, size.x, size.y);

    node.attribute("width").set_value(size.x);
    node.attribute("height").set_value(size.y);
    game->document.save_file("config.xml");
}

void Window::CenterWindowPosition()
{
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::SetTitle(const char* title)
{
    SDL_SetWindowTitle(window, title);
}

void Window::SetState(Window::State state)
{
    this->state = state;
}
