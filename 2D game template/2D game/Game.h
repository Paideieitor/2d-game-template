#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <iostream>
#include "pugixml.hpp"
#include "Point.h"
#include "Color.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/lib/SDL2.lib" )
#pragma comment( lib, "SDL/lib/SDL2main.lib" )

using namespace std;

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

	Render* render;

	pugi::xml_document document;

	//FUNCTIONALITY
	fpoint Center(ipoint objsize, fpoint position, ipoint size, fpoint objposition = { 0,0 }, bool horizontal = true, bool vertical = true);
	int StringToInt(string);
	string IntToString(int);

private:

	void AddModule(Module* module, bool active = true);
	vector<Module*> modules;
};

extern Game* game;

#endif