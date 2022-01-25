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

	void DisableAll();
	void EnableAll();

	const bool IsListModify() { return listmodify; }

private:

	void AddElement(UIElement* element);
	void EraseElement(UIElement* element);
	bool IsFocused(UIElement*);

private:

	bool listmodify = false;
	std::vector<UIElement*> elements;

	friend class UIElement;
};

#endif