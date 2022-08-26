#include "MainMenu.h"

#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "SceneManager.h"

#include "OptionsMenu.h"

#include "Textures.h"
#include "Fonts.h"
#include "UIManager.h"
#include "EntityManager.h"

//TEST
#include "Physics.h"

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
	backgroundImg = game->textures->Load("images/forest.png");

	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	play = game->ui->AddButton("Play", buttonfont, Color::black, { 0.0f, 0.0f });
	play->SetPosition(game->Center(play->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,100 }, true, false));

	tooptions = game->ui->AddButton("Options", buttonfont, Color::black, { 0.0f, 0.0f });
	tooptions->SetPosition(game->Center(tooptions->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,250 }, true, false));

	exit = game->ui->AddButton("Exit", buttonfont, Color::black, {0.0f, 0.0f});
	exit->SetPosition(game->Center(exit->GetSize(), { 0,0 }, game->render->GetResolution(true), { 0,400 }, true, false));

	box = game->ui->AddInputBox(buttonfont, Color::black, fpoint(20.0f, 20.0f));

	player = game->entities->AddPlayer("Ron", { 400,-500 }, 0);

	camera = game->entities->AddCamara(fpoint(400, -500));
	camera->Follow(player, 0.1f, 10.0f, true);
	
	return true;
}

bool MainMenu::Update(float dt)
{
	game->render->RenderTexture(false, 5, test, { 50,100 }, 0, 0, test->GetSize(), false, 255, true);
	game->render->RenderTexture(false, 5, backgroundImg, { 0,0 }, 0, 0, backgroundImg->GetSize(), false, 255, true);

	game->physics->PhysicsDebugDraw();

	//if (game->input->CheckState(Key::MOUSE_LEFT) == Input::State::DOWN && !game->ui->IsHovering())
		//camera->Move(game->input->GetMousePos(true), 1.0f, 1.0f, false);

	return true;
} 

bool MainMenu::CleanUp()
{
	test = nullptr;
	backgroundImg = nullptr;

	buttonfont = nullptr;

	game->ui->EraseElement(play);
	game->ui->EraseElement(tooptions);
	game->ui->EraseElement(exit);
	game->ui->EraseElement(box);

	game->entities->EraseEntity(camera);
	game->entities->EraseEntity(player);

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