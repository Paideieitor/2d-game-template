#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Module.h"

class Scene;

class SceneManager : public Module
{
public:

	SceneManager();
	~SceneManager();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void ChangeScene(const std::string& name);
	const bool ChangingScenes() const { return changing; }

	Scene* currentscene;

	pugi::xml_node mainnode;

private:

	Scene* nextscene;

	std::vector<Scene*> scenes;

	bool changing;
};

#endif
