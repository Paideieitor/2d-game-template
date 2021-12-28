#include "OptionsMenu.h"

#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "SceneManager.h"

#include "Fonts.h"
#include "Textures.h"

#include "Button.h"
#include "ButtonArray.h"
#include "Scrollbar.h"

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

	game->window->SetGrabbed(false);

	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	fullscreen = new Button("Fullscreen", buttonfont, Color::black, { 0.0f, 0.0f }, nullptr, Button::Type::LOCKONCLICK);
	fullscreen->SetPosition(game->Center(fullscreen->GetSize(), { 0,0 }, game->render->resolution, { 0,100 }, true, false));
	fullscreen->Lock(game->window->IsFullscreen());

	borderless = new Button("Borderless", buttonfont, Color::black, { 0.0f, 0.0f });
	borderless->SetPosition(game->Center(borderless->GetSize(), { 0,0 }, game->render->resolution, { 0,250 }, true, false));

	vector<string> resolutuonoptions;
	pugi::xml_node arraynode = game->scenes->mainnode.child(name.c_str()).child("resolution");
	int current = arraynode.attribute("current").as_int();
	pugi::xml_node button = arraynode.first_child();
	for (button; button != NULL; button = button.next_sibling())
		resolutuonoptions.push_back(button.attribute("name").as_string());
	resolution = new ButtonArray("Resolution", buttonfont, Color::black, resolutuonoptions, fpoint(0, 0));
	resolution->SetPosition(game->Center(resolution->GetSize(), { 0,0 }, game->render->resolution, { 0,400 }, true, false));

	music = new Scrollbar("Music", buttonfont, Color::black, { 0.0f, 0.0f }, nullptr, Scrollbar::Type::INT);
	music->SetPosition(game->Center(music->GetSize(), { 0,0 }, game->render->resolution, { 0,550 }, true, false));
	music->SetValue((float)game->audio->GetMusicVolume());

	sfx = new Scrollbar("SFX", buttonfont, Color::black, { 0.0f, 0.0f }, nullptr, Scrollbar::Type::INT);
	sfx->SetPosition(game->Center(sfx->GetSize(), { 0,0 }, game->render->resolution, { 0,700 }, true, false));
	sfx->SetValue((float)game->audio->GetSfxVolume());

	tomenu = new Button("Main Menu", buttonfont, Color::black, { 0.0f, 0.0f });
	tomenu->SetPosition(game->Center(tomenu->GetSize(), { 0,0 }, game->render->resolution, { 0,850 }, true, false));

	return true;
}

bool OptionsMenu::Update(float dt)
{
	game->render->RenderRectangle(0, { 0,0 }, game->render->resolution.x, game->render->resolution.y, *background);

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
		game->window->SetFullscreen(!game->window->IsFullscreen());
	else if (element == borderless)
		game->window->SetBorderless(!game->window->IsBorderless());
	else if (element == resolution)
	{
		string current = resolution->GetCurrent();
		int cut = current.find_first_of('x');
		ipoint res;
		res.x = game->StringToInt(current.substr(0, cut));
		res.y = game->StringToInt(current.substr(cut + 1));
		
		game->window->SetWindowSize(res);
		game->window->CenterWindowPosition();
	}
	else if (element == music)
		game->audio->SetMusicVolume((int)music->GetValue());
	else if (element == sfx)
		game->audio->SetSfxVolume((int)sfx->GetValue());
	else if (element == tomenu)
		game->scenes->ChangeScene(Scenes::MENU);
}