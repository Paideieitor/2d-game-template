#include "Scenes.h"

#include "BOX2D/Box2D/Box2D.h"
#include "Render.h"
#include "Window.h"
#include "SceneManager.h"

//TEST
#include "Physics.h"
#include "PhysicsComponent.h"
//

MainMenu::MainMenu()
{
	name = "menu";
}

MainMenu::~MainMenu()
{

}

bool MainMenu::Start()
{
	background = new Color(255,255,0,255);

	buttonfont = game->fonts->Load("fonts/overpass/regular.ttf", 45);

	tooptions = new Button("options menu", buttonfont, game->Center({ 300,70 }, { 0,0 }, game->render->resolution, { 0,100 }, true, false), { 300,70 }, { 255,0,0,255 });
	exit = new Button("exit to desktop", buttonfont, game->Center({ 300,70 }, { 0,0 }, game->render->resolution, { 0,250 }, true, false), { 300,70 }, { 0,255,0,255 });

	test = game->textures->Load("images/Chadkino.png");

	box = new InputBox("", buttonfont, { 0,0 }, { 300,100 }, { 100,100,100 });

	return true;
}

bool MainMenu::Update(float dt)
{
	game->render->AddTextureEvent(5, test, { 50,100 }, 0, 0, test->GetSize(), false, 255, true, 1.0f, 30, fpoint(test->GetSize().x/2,test->GetSize().y/2));

	//TEST
	game->render->AddRectangleEvent(5, { game->physics->box->GetBody()->GetPosition().x,-game->physics->box->GetBody()->GetPosition().y }, 30, 30, { 122, 129, 10, 255 });
	game->render->AddRectangleEvent(5, { game->physics->box1->GetBody()->GetPosition().x,-game->physics->box1->GetBody()->GetPosition().y }, 30, 30, { 222, 12, 10, 255 });
	game->render->AddRectangleEvent(5, { game->physics->box2->GetBody()->GetPosition().x,-game->physics->box2->GetBody()->GetPosition().y }, 30, 30, { 2, 129, 10, 55 });
	game->render->AddRectangleEvent(5, { game->physics->groundBody->GetPosition().x,-game->physics->groundBody->GetPosition().y }, 5000, 12, { 122, 129, 10, 255 });
	//
	game->render->AddRectangleEvent(0, { 0,0 }, game->render->resolution.x, game->render->resolution.y, *background);

	return true;
} 

bool MainMenu::CleanUp()
{
	delete background;

	buttonfont = nullptr;

	return true;
}

void MainMenu::UIEvent(UIElement* element)
{
	if (element == tooptions)
		game->scenes->ChangeScene(game->scenes->options);
	else if (element == exit)
		game->window->SetState(windowstate::QUIT);
	else if (element == box)
		game->window->SetTitle(box->GetContent().c_str());
}