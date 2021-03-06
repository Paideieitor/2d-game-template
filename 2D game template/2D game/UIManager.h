#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Module.h"

class UIElement;

class UIManager : public Module
{
public:

	UIManager();
	~UIManager();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void DestroyElement(UIElement*);
	void EraseElement(UIElement* element);

	vector<UIElement*> elements;
};

#endif