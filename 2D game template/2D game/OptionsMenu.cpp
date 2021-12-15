#include "Scenes.h"

#include "Render.h"
#include "Window.h"
#include "Audio.h"

OptionsMenu::OptionsMenu()
{
	name = "options";
}

OptionsMenu::~OptionsMenu()
{

}

bool OptionsMenu::Start()
{
	background = new Color(150,150,200,255);

	game->window->grabbed = false;
	SDL_SetWindowGrab(game->window->window, SDL_FALSE);

	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	fullscreen = new Button("fullscreen", buttonfont, game->Center({ 300,70 }, { 0,0 }, game->render->resolution, { 0,100 }, true, false), { 300,70 }, { 75,75,255,255 });

	borderless = new Button("borderless", buttonfont, game->Center({ 300,70 }, { 0,0 }, game->render->resolution, { 0,250 }, true, false), { 300,70 }, { 75,75,255,255 });

	resolution = new ButtonArray("resolution", buttonfont, game->Center({ 400,70 }, { 0,0 }, game->render->resolution, { 0,400 }, true, false), { 400,70 }, { 75,75,255,255 });

	music = new Scrollbar("music", buttonfont, game->Center({ 500,20 }, { 0,0 }, game->render->resolution, { 0,550 }, true, false), { 500,20 }, { 0,0,255,255 }, (float)game->audio->GetMusicVolume(), buttonfont, true);

	sfx = new Scrollbar("sfx", buttonfont, game->Center({ 500,20 }, { 0,0 }, game->render->resolution, { 0,700 }, true, false), { 500,20 }, { 0,0,255,255 }, (float)game->audio->GetSfxVolume(), buttonfont, true);

	tomenu = new Button("main menu", buttonfont, game->Center({ 300,70 }, { 0,0 }, game->render->resolution, { 0,850 }, true, false), { 300,70 }, { 75,75,255,255 });

	return true;
}

bool OptionsMenu::Update(float dt)
{
	game->render->AddRectangleEvent(0, { 0,0 }, game->render->resolution.x, game->render->resolution.y, *background);

	return true;
}

bool OptionsMenu::CleanUp()
{
	delete background;

	buttonfont = nullptr;

	return true;
}

void OptionsMenu::UIEvent(UIElement* element)
{
	if (element == fullscreen)
	{ 
		pugi::xml_node node = game->document.first_child().child(game->window->name.c_str()).child("fullscreen");
		bool fullscreen = node.attribute("value").as_bool();
		
		if (fullscreen)
		{
			SDL_SetWindowFullscreen(game->window->window, 0);
			node.attribute("value").set_value("false");
		}
		else
		{
			SDL_SetWindowFullscreen(game->window->window, SDL_WINDOW_FULLSCREEN);
			node.attribute("value").set_value("true");
		}
		
		game->document.save_file("config.xml");
	}
	else if (element == borderless)
	{
		pugi::xml_node node = game->document.first_child().child(game->window->name.c_str()).child("borderless");
		bool borderless = !node.attribute("value").as_bool();

		SDL_SetWindowBordered(game->window->window, (SDL_bool)!borderless);
		node.attribute("value").set_value(borderless);

		game->document.save_file("config.xml");
	}
	else if (element == resolution)
	{
		string current = resolution->GetArrayCurrent();
		string x;
		string y;
		ipoint res;
		
		bool change = false;
		for (string::iterator s = current.begin(); s != current.end(); s++)
		{
			if (!change)
				if (*s != 'x')
					x.push_back(*s);
				else
					change = true;
			else
				y.push_back(*s);
		}
		
		res.x = game->StringToInt(x);
		res.y = game->StringToInt(y);
		
		SDL_SetWindowSize(game->window->window, res.x, res.y);
		SDL_SetWindowPosition(game->window->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		
		pugi::xml_node node = game->document.first_child().child(game->window->name.c_str());
		
		node.attribute("width").set_value(res.x);
		node.attribute("height").set_value(res.y);
		
		game->document.save_file("config.xml");
	}
	else if (element == music)
	{
		int volume = (int)music->GetBarValue();

		game->audio->SetMusicVolume(volume);
	}
	else if (element == sfx)
	{
		int volume = (int)sfx->GetBarValue();

		game->audio->SetSfxVolume(volume);
	}
	else if (element == tomenu)
	{
		game->window->grabbed = true;
		SDL_SetWindowGrab(game->window->window, SDL_TRUE);
		game->scenes->ChangeScene(game->scenes->menu);
	}

}