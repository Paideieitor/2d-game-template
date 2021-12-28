#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Module.h"

class Scene;
class MainMenu;
class OptionsMenu;

enum class Scenes
{
	NONE,
	MENU,
	OPTIONS
};

class SceneManager : public Module
{
public:

	SceneManager();
	~SceneManager();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void ChangeScene(Scenes);
	const bool ChangingScenes() const { return changing; }

	MainMenu* menu;
	OptionsMenu* options;

	Scene* currentscene;

	pugi::xml_node mainnode;

private:

	Scene* nextscene;

	vector<Scene*> scenes;

	bool changing;
};

#endif
