#include "SceneManager.h"

#include "MainMenu.h"
#include "OptionsMenu.h"

#include "Input.h"
#include "UIManager.h"
#include "Textures.h"
#include "Render.h"

#include<thread>

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

	ChangeScene("Main Menu");

	return true;
}

bool SceneManager::Update(float dt)
{
	if (game->input->CheckState(Key::F1) == Input::State::DOWN)
		ChangeScene("Main Menu");

	if (nextscene != currentscene)
	{
		if (currentscene != nullptr)
			currentscene->CleanUp();

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

const std::vector<std::string> SceneManager::GetButtonArrayOptions(const std::string& scene, const std::string& buttonatrray, int& current) const
{
	std::vector<std::string> output;
	pugi::xml_node arraynode = game->scenes->mainnode.child(scene.c_str()).child(buttonatrray.c_str());

	current = arraynode.attribute("current").as_int();
	for (pugi::xml_node button = arraynode.first_child(); button != NULL; button = button.next_sibling())
		output.push_back(button.attribute("name").as_string());

	return output;
}

void SceneManager::SetButtonArrayCurrent(const std::string& scene, const std::string& buttonatrray, const int current)
{
	pugi::xml_node arraynode = game->scenes->mainnode.child(scene.c_str()).child(buttonatrray.c_str());
	arraynode.attribute("current").set_value(current);
	game->document.save_file("config.xml");
}
