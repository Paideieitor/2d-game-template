#include "MainMenu.h"

#include "Render.h"
#include "Window.h"
#include "SceneManager.h"

#include "OptionsMenu.h"

#include "Textures.h"
#include "Fonts.h"

#include "Button.h"
#include "InputBox.h"
#include "Label.h"

//TEST
#include "Physics.h"
#include "Player.h"

MainMenu::MainMenu() : Scene("Main Menu"), test(nullptr)
{
}

MainMenu::~MainMenu()
{

}

bool MainMenu::Start()
{
	game->render->background = Color(255,255,0,255);

	test = game->textures->Load("images/Chadkino.png");
	backgroundImg = game->textures->Load("images/BG12.png");
	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	play = new Button("Play", buttonfont, Color::black, { 0.0f, 0.0f });
	play->SetPosition(game->Center(play->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,100 }, true, false));

	tooptions = new Button("Options", buttonfont, Color::black, { 0.0f, 0.0f });
	tooptions->SetPosition(game->Center(tooptions->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,250 }, true, false));

	exit = new Button("Exit", buttonfont, Color::black, {0.0f, 0.0f});
	exit->SetPosition(game->Center(exit->GetSize(), { 0,0 }, game->render->GetResolution(), { 0,400 }, true, false));

	box = new InputBox(buttonfont, Color::black, fpoint(20.0f, 20.0f));

	player = new Player("Ron", { 400,-900 }, 0);
	
	return true;
}

bool MainMenu::Update(float dt)
{
	//game->render->RenderTexture(5, test, { 50,100 }, 0, 0, test->GetSize(), false, 255, false);
	game->render->RenderTexture(1, backgroundImg, { 0,0 }, 0, 0, backgroundImg->GetSize()*6, false, 255,true);
	//Physics test
	game->physics->PhysicsDebugDraw();

	return true;
} 

bool MainMenu::CleanUp()
{
	test = nullptr;

	buttonfont = nullptr;

	delete play;
	delete tooptions;
	delete exit;
	delete box;

	delete player;

	return true;
}

void MainMenu::UIEvent(UIElement* element)
{
	if (element == play)
		game->Log("Straight up NO GAME");
	else if (element == tooptions)
		new OptionsMenu();
	else if (element == exit)
		game->window->SetState(Window::State::QUIT);
	else if (element == box)
		game->window->SetTitle(box->GetContent().c_str());
}