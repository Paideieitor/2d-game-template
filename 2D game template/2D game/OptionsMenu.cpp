#include "OptionsMenu.h"

#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "SceneManager.h"
#include "UIManager.h"

#include "Fonts.h"
#include "Textures.h"

#include "Button.h"
#include "ButtonArray.h"
#include "Scrollbar.h"

OptionsMenu::OptionsMenu() : Scene("Options Menu")
{
	game->ui->DisableAll();

	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	fullscreen = new Button("Fullscreen", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), Button::Type::LOCKONCLICK, false, this);
	fullscreen->SetPosition(game->Center(fullscreen->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,100 }, true, false));
	fullscreen->Lock(game->window->IsFullscreen());

	borderless = new Button("Borderless", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), Button::Type::SINGLECLICK, false, this);
	borderless->SetPosition(game->Center(borderless->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,250 }, true, false));

	int current = 0;
	const std::vector<std::string> resolutuonoptions = game->scenes->GetButtonArrayOptions("options", "resolution", current);
	resolution = new ButtonArray("Resolution", buttonfont, Color::black, resolutuonoptions, fpoint(0, 0),UIGraphics(), UIGraphics(), UIGraphics(), false, this);
	resolution->SetPosition(game->Center(resolution->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,400 }, true, false));
	resolution->SetCurrent(current);

	music = new Scrollbar("Music", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), UIGraphics(), Scrollbar::Type::INT, false, this);
	music->SetPosition(game->Center(music->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,550 }, true, false));
	music->SetValue((float)game->audio->GetMusicVolume());

	sfx = new Scrollbar("SFX", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), UIGraphics(), Scrollbar::Type::INT, false, this);
	sfx->SetPosition(game->Center(sfx->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,700 }, true, false));
	sfx->SetValue((float)game->audio->GetSfxVolume());

	tomenu = new Button("Main Menu", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), Button::Type::SINGLECLICK, false, this);
	tomenu->SetPosition(game->Center(tomenu->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,850 }, true, false));
}

OptionsMenu::~OptionsMenu()
{
	buttonfont = nullptr;

	delete fullscreen;
	delete borderless;
	delete resolution;
	delete music;
	delete sfx;
	delete tomenu;

	game->ui->EnableAll();
}

bool OptionsMenu::Update(float dt)
{
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
		std::string current = resolution->GetCurrent();
		game->scenes->SetButtonArrayCurrent("options", "resolution", resolution->GetIndex());
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
		delete this;
}