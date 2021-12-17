#include "Observer.h"

#include "UIElement.h"
#include "Scenes.h"
//#include "Entity.h"

void Observer::Fill(UIElement* element)
{
	type = Type::ELEMENT;
	this->element = element;
	scene = nullptr;
	entity = nullptr;
}

void Observer::Fill(Scene* scene)
{
	type = Type::SCENE;
	element = nullptr;
	this->scene = scene;
	entity = nullptr;
}

void Observer::Fill(Entity* entity)
{
	type = Type::ENTITY;
	element = nullptr;
	scene = nullptr;
	this->entity = entity;
}

const char* Observer::GetName()
{
	switch (type)
	{
	case Type::ELEMENT:
		return element->name.c_str();
	case Type::SCENE:
		return scene->name.c_str();
	case Type::ENTITY:
		break;//return entity->name.c_str();
	}
	return nullptr;
}

void Observer::UIEvent(UIElement* reporter) const
{
	switch (type)
	{
	case Type::ELEMENT:
		element->UIEvent(reporter);
		break;
	case Type::SCENE:
		scene->UIEvent(reporter);
		break;
	case Type::ENTITY:
		//entity->UIEvent(reporter);
		break;
	}
}
