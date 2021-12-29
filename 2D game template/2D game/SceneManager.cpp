#include "SceneManager.h"

#include "MainMenu.h"
#include "OptionsMenu.h"

#include "Input.h"
#include "UIManager.h"
#include "Textures.h"
#include "Render.h"

SceneManager::SceneManager()
{
	name = "scenemanager";
	changing = false;
}

SceneManager::~SceneManager()
{

}

bool SceneManager::SetUp(pugi::xml_node& node)
{
	mainnode = node;

	return true;
}

bool SceneManager::Start()
{
	menu = new MainMenu();
	options = new OptionsMenu();

	ChangeScene(Scenes::MENU);

	return true;
}

bool SceneManager::Update(float dt)
{
	if (game->input->CheckState(Key::F1) == Input::State::DOWN)
		ChangeScene(Scenes::OPTIONS);
	if (game->input->CheckState(Key::F2) == Input::State::DOWN)
		ChangeScene(Scenes::MENU);

	if (nextscene != currentscene)
	{
		if (currentscene != nullptr)
		{
			currentscene->CleanUp();
			game->ui->CleanUp();
			game->fonts->CleanUp();
			game->textures->CleanUp();
			game->render->ClearEvents();
		}

		currentscene = nextscene;
		changing = false;

		if (currentscene != nullptr)
			currentscene->Start();
	}

	if (!currentscene->Update(dt))
	{
		cout << "Scene Manager Update -> Bad Thing, Error in " << currentscene->name << endl;
		return false;
	}

	return true;
}

bool SceneManager::CleanUp()
{
	if (currentscene && !currentscene->CleanUp())
	{
		cout << "Scene Manager Clean Up -> Bad Thing, Error in " << currentscene->name << endl;
		return false;
	}

	while (scenes.size() != 0)
	{
		delete* scenes.begin();
		scenes.erase(scenes.begin());
	}

	return true;
}

void SceneManager::ChangeScene(Scenes scene)
{
	Scene* nextscene = nullptr;
	switch (scene)
	{
	case Scenes::NONE:
		break;
	case Scenes::MENU:
		nextscene = menu;
		break;
	case Scenes::OPTIONS:
		nextscene = options;
		break;
	}
	if (nextscene != currentscene)
	{
		this->nextscene = nextscene;
		changing = true;
	}
}