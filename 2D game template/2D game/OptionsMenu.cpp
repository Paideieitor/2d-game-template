#include "OptionsMenu.h"

#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "SceneManager.h"
#include "UIManager.h"

#include "Fonts.h"
#include "Textures.h"
#include "UIManager.h"

OptionsMenu::OptionsMenu() : Scene("Options Menu")
{
	disablelist = game->ui->DisableAll();

	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	fpscap = game->ui->AddScrollbar("FPS Cap", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), UIGraphics(), UIGraphics(), Scrollbar::Type::INT, false, this);
	fpscap->SetPosition(game->Center(fpscap->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,100 }, true, false));
	fpscap->SetMinMax(5.0f, 300.0f);
	fpscap->SetValue((float)game->GetFPSCap());

	fullscreen = game->ui->AddButton("Fullscreen", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), Button::Type::LOCKONCLICK, false, this);
	fullscreen->SetPosition(game->Center(fullscreen->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,200 }, true, false));
	fullscreen->Lock(game->window->IsFullscreen());

	borderless = game->ui->AddButton("Borderless", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), Button::Type::SINGLECLICK, false, this);
	borderless->SetPosition(game->Center(borderless->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,350 }, true, false));

	int current = 0;
	const std::vector<std::string> resolutuonoptions = game->scenes->GetButtonArrayOptions("options", "resolution", current);
	resolution = game->ui->AddButtonArray("Resolution", buttonfont, Color::black, resolutuonoptions, fpoint(0, 0),UIGraphics(), UIGraphics(), UIGraphics(), false, this);
	resolution->SetPosition(game->Center(resolution->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,500 }, true, false));
	resolution->SetCurrent(current);

	music = game->ui->AddScrollbar("Music", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), UIGraphics(), UIGraphics(), Scrollbar::Type::INT, false, this);
	music->SetPosition(game->Center(music->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,650 }, true, false));
	music->SetValue((float)game->audio->GetMusicVolume());

	//sfx = game->ui->AddScrollbar("SFX", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), UIGraphics(), UIGraphics(), Scrollbar::Type::INT, false, this);
	//sfx->SetPosition(game->Center(sfx->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,800 }, true, false));
	//sfx->SetValue((float)game->audio->GetSfxVolume());

	tomenu = game->ui->AddButton("Main Menu", buttonfont, Color::black, { 0.0f, 0.0f }, UIGraphics(), Button::Type::SINGLECLICK, false, this);
	tomenu->SetPosition(game->Center(tomenu->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,900 }, true, false));
}

OptionsMenu::~OptionsMenu()
{
	buttonfont = nullptr;

	game->ui->EraseElement(fpscap);
	game->ui->EraseElement(fullscreen);
	game->ui->EraseElement(borderless);
	game->ui->EraseElement(resolution);
	game->ui->EraseElement(music);
	game->ui->EraseElement(sfx);
	game->ui->EraseElement(tomenu);

	game->ui->EnableAll(disablelist);
}

bool OptionsMenu::Update(float dt)
{
	return true;
}

void OptionsMenu::UIEvent(UIElement* element)
{
	if (element == fpscap)
		game->SetFPSCap((int)fpscap->GetValue());
	else if (element == fullscreen)
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