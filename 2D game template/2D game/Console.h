#include "Module.h"
#include "UIElements.h"

class Console : public Module
{
public:

	Console();
	~Console();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void UIEvent(UIElement*);

	vector<string> history;

private:

	bool display;

	InputBox* input;
	Scrollbar* scroll;

	Font* font;
};
