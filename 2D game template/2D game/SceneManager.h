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

	Scene* const CurrentScene() const { return currentscene; }

	const std::vector<std::string> GetButtonArrayOptions(const std::string& scene, const std::string& buttonatrray, int& current) const;
	void SetButtonArrayCurrent(const std::string& scene, const std::string& buttonatrray, const int current);

private:

	Scene* currentscene;
	Scene* nextscene;
	std::vector<Scene*> scenes;

	bool changing;

	pugi::xml_node mainnode;
};

#endif
