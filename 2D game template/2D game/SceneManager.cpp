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
	scenes.emplace_back(new MainMenu());
	scenes.emplace_back(new OptionsMenu());

	ChangeScene("Main Menu");

	return true;
}

bool SceneManager::Update(float dt)
{
	if (game->input->CheckState(Key::F1) == Input::State::DOWN)
		ChangeScene("Options Menu");
	if (game->input->CheckState(Key::F2) == Input::State::DOWN)
		ChangeScene("Main Menu");

	if (nextscene != currentscene)
	{
		if (currentscene != nullptr)
		{
			currentscene->CleanUp();
			game->ui->CleanUp();
		}

		currentscene = nextscene;
		changing = false;

		if (currentscene != nullptr)
			currentscene->Start();
	}

	if (!currentscene->Update(dt))
	{
		game->Log("Scene Manager Update -> Bad Thing, Error in " + currentscene->name);
		return false;
	}

	return true;
}

bool SceneManager::CleanUp()
{
	if (currentscene && !currentscene->CleanUp())
	{
		game->Log("Scene Manager Clean Up -> Bad Thing, Error in " + currentscene->name);
		return false;
	}

	while (scenes.size() != 0)
	{
		delete* scenes.begin();
		scenes.erase(scenes.begin());
	}

	return true;
}

void SceneManager::ChangeScene(const std::string& name)
{
	Scene* nextscene = nullptr;
	for (size_t i = 0; i < scenes.size(); ++i)
		if (scenes[i]->name == name)
		{
			nextscene = scenes[i];
			break;
		}

	if (nextscene != currentscene)
	{
		this->nextscene = nextscene;
		changing = true;
	}
}