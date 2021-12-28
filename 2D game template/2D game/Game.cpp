#include "Game.h"
#include "Module.h"

#include "Input.h"
#include "Fonts.h"
#include "Window.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "AssetManager.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Console.h"

#include <sstream>

Game::Game()
{
	input = new Input();
	fonts = new Fonts();
	window = new Window();
	scenes = new SceneManager();
	ui = new UIManager();
	assets = new AssetManager();
	textures = new Textures();
	render = new Render();
	audio = new Audio();
	//console = new Console();

	AddModule(input);
	//FIRST ^
	AddModule(window);
	AddModule(assets);
	AddModule(textures);
	AddModule(audio);
	AddModule(fonts);
	AddModule(ui);
	//AddModule(console);
	AddModule(scenes);
	//LAST  v
	AddModule(render);
}

Game::~Game()
{
	while (modules.size() != 0)
		modules.erase(modules.begin());
}

bool Game::SetUp()
{
	bool output = true;

	pugi::xml_parse_result result = document.load_file("config.xml");

	for (vector<Module*>::iterator m = modules.begin(); m != modules.end(); m++)
	{
		Module* module = *m;

		pugi::xml_node node = document.first_child().child(module->name.c_str());
		output = module->SetUp(node);

		if (!output)
		{
			cout << "Set Up -> Bad Thing, Error in " << module->name << endl;
			break;
		}
	}

	return output;
}

bool Game::Start()
{
	bool output = true;

	for (vector<Module*>::iterator m = modules.begin(); m != modules.end(); m++)
	{
		Module* module = *m;

		output = module->Start();

		if (!output)
		{
			cout << "Start -> Bad Thing, Error in " << module->name << endl;
			break;
		}
	}

	return output;
}

bool Game::Update()
{
	bool output = true;

	for (vector<Module*>::iterator m = modules.begin(); m != modules.end(); m++)
	{
		Module* module = *m;

		output = module->Update(0.0f);

		if (!output)
		{
			cout << "Update -> Bad Thing, Error in " << module->name << endl;
			break;
		}
	}

	return output;
}

bool Game::CleanUp()
{
	bool output = true;

	for (vector<Module*>::iterator m = modules.end() - 1; m != modules.begin(); m--)
	{
		Module* module = *m;

		output = module->CleanUp();
		delete module;

		if (!output)
		{
			cout << "Clean Up -> Bad Thing, Error in " << module->name << endl;
			break;
		}
	}

	return output;
}

void Game::AddModule(Module* module, bool active)
{
	if (!active)
		module->Deinit();

	modules.push_back(module);
}

fpoint Game::Center(ipoint objsize, fpoint position, ipoint size, fpoint objposition, bool horizontal, bool vertical)
{
	fpoint output;

	if (horizontal)
		output.x = (position.x + size.x / 2) - objsize.x / 2;
	else
		output.x = objposition.x;

	if (vertical)
		output.y = (position.y + size.y / 2) - objsize.y / 2;
	else
		output.y = objposition.y;

	return output;
}

ipoint Game::ResizeIPoint(const ipoint& size, float multiplier)
{
	float x = (float)size.x, y = (float)size.y;
	x *= multiplier;
	y *= multiplier;

	return ipoint((int)x, (int)y);
}

int Game::StringToInt(string number)
{
	int output;
	stringstream stream;

	stream << number;
	stream >> output;

	return output;
}

string Game::IntToString(int number)
{
	string output;
	stringstream stream;

	stream << number;
	stream >> output;

	return output;
}

string Game::FloatToString(float number)
{
	string output;
	stringstream stream;

	stream << number;
	stream >> output;

	return output;
}
