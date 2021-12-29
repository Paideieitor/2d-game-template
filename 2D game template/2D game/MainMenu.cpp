#include "MainMenu.h"

#include "Render.h"
#include "Window.h"
#include "SceneManager.h"

#include "Textures.h"
#include "Fonts.h"

#include "Button.h"
#include "InputBox.h"
#include "Label.h"

//TEST
#include "Physics.h"

MainMenu::MainMenu()
{
	name = "menu";
}

MainMenu::~MainMenu()
{

}

bool MainMenu::Start()
{
	background = Color(255,255,0,255);

	game->window->SetGrabbed(true);

	test = game->textures->Load("images/Chadkino.png");

	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	play = new Button("Play", buttonfont, Color::black, { 0.0f, 0.0f });
	play->SetPosition(game->Center(play->GetSize(), { 0,0 }, game->render->resolution, { 0,100 }, true, false));

	tooptions = new Button("Options", buttonfont, Color::black, { 0.0f, 0.0f });
	tooptions->SetPosition(game->Center(tooptions->GetSize(), { 0,0 }, game->render->resolution, { 0,250 }, true, false));

	exit = new Button("Exit", buttonfont, Color::black, {0.0f, 0.0f});
	exit->SetPosition(game->Center(exit->GetSize(), { 0,0 }, game->render->resolution, { 0,400 }, true, false));

	box = new InputBox(buttonfont, Color::black, fpoint(20.0f, 20.0f));

	label = new Label("Test Label", buttonfont, Color::red, { 300,100 });
	
	return true;
}

bool MainMenu::Update(float dt)
{
	game->render->RenderTexture(5, test, { 50,100 }, 0, 0, test->GetSize());

	//Physics test
	game->physics->PhysicsDebugDraw();

	game->render->RenderRectangle(0, { 0,0 }, game->render->resolution.x, game->render->resolution.y, background);

	return true;
} 

bool MainMenu::CleanUp()
{
	game->textures->Unload(test);

	game->fonts->Unload(buttonfont);

	delete play;
	delete tooptions;
	delete exit;
	delete box;
	delete label;

	return true;
}

void MainMenu::UIEvent(UIElement* element)
{
	if (element == play)
		cout << "Straight up NO GAME" << endl;
	else if (element == tooptions)
		game->scenes->ChangeScene(Scenes::OPTIONS);
	else if (element == exit)
		game->window->SetState(windowstate::QUIT);
	else if (element == box)
		game->window->SetTitle(box->GetContent().c_str());
}