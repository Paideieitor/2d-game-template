#ifndef GAME_H
#define GAME_H

#include "Point.h"
#include "Color.h"
#include "Timer.h"

#include "pugixml.hpp"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Module;

class Input;

class Fonts;
class Window;
class SceneManager;
class UIManager;
class AssetManager;
class Textures;
class Audio;
class Console;
class Physics;
class EntityManager;

class Render;

class Game
{
public:

	Game();
	~Game();

	bool SetUp();

	bool Start();
	bool Update();
	bool CleanUp();

	Input* input;

	Fonts* fonts;
	Window* window;
	SceneManager* scenes;
	UIManager* ui;
	AssetManager* assets;
	Textures* textures;
	Audio* audio;
	Console* console;
	Physics* physics;
	EntityManager* entities;

	Render* render;

	pugi::xml_document document;

	//FUNCTIONALITY
	fpoint Center(ipoint objsize, fpoint position, ipoint size, fpoint objposition = { 0,0 }, bool horizontal = true, bool vertical = true);
	ipoint ResizeIPoint(const ipoint& size, float multiplier);

	int StringToInt(std::string);
	std::string IntToString(int);
	std::string FloatToString(float);

	void Log(const std::string& log) const { std::cout << log << "\n"; }

private:

	void AddModule(Module* module, bool active = true);
	std::vector<Module*> modules;

	int frameMs;
	int timeToDelay;
	int frameCap = 240;
	float dt = 0;
	Timer time;
};

extern Game* game;

#endif