#ifndef INPUT_H
#define INPUT_H

#define MAX_KEYS 300
#define MAX_BUTTONS 10

#include "Module.h"

enum keystate
{
	IDLE,
	REPEAT,
	UP,
	DOWN,
};

class Input : public Module
{
public:

	Input();
	~Input();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	keystate GetKey(int) const;
	keystate GetButton(int) const;

	fpoint GetMousePos(bool usescale = true) const;

	bool GetTextInput(char &input);

private:

	char textinput;
	bool inputrecieved;

	fpoint mouse;

	keystate keyboard[MAX_KEYS];
	keystate mousebuttons[MAX_BUTTONS];
};

#endif
