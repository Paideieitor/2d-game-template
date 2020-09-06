#include "Window.h"
#include <iostream>

using namespace std;

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
    width = node.attribute("width").as_int();
    height = node.attribute("height").as_int();
    scale = node.attribute("scale").as_float();
    
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED;
    grabbed = true;

    if (node.child("fullscreen").attribute("value").as_bool() == true)
        flags |= SDL_WINDOW_FULLSCREEN;
    if (node.child("borderless").attribute("value").as_bool() == true)
        flags |= SDL_WINDOW_BORDERLESS;

    window = SDL_CreateWindow("Archipielago", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

    if (window == NULL)
    {
        cout << "Window -> Bad Thing, Error: " << SDL_GetError() << endl;
        return false;
    }

	return true;
}

bool Window::Start()
{
    state = windowstate::SHOW;

	return true;
}

bool Window::Update(float dt)
{
    switch (state)
    {
    case windowstate::QUIT:
        return false;
        break;
    case windowstate::HIDE:
        break;
    case windowstate::SHOW:
        break;
    }

	return true;
}

bool Window::CleanUp()
{

	return true;
}