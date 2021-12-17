#ifndef UIOBSERVER_H
#define UIOBSERVER_H

class UIElement;
class Scene;
class Entity;

class Observer
{
private:
	enum class Type
	{
		EMPTY,
		ELEMENT,
		SCENE,
		ENTITY
	};
	Type type;

public:
	Observer() : type(Type::EMPTY), element(nullptr), scene(nullptr), entity(nullptr) {}

	Observer(UIElement* element) : type(Type::ELEMENT), element(element), scene(nullptr), entity(nullptr) {}
	Observer(Scene* scene) : type(Type::SCENE), element(nullptr), scene(scene), entity(nullptr) {}
	Observer(Entity* entity) : type(Type::ENTITY), element(nullptr), scene(nullptr), entity(entity) {}

	void Fill(UIElement* element);
	void Fill(Scene* scene);
	void Fill(Entity* entity);

	bool IsEmpty() const { return type == Type::EMPTY ? true : false; } // I just used a ternary from memory, how am i unemployed?
	const char* GetName();

	void UIEvent(UIElement* reporter) const;

private:

	UIElement* element;
	Scene* scene;
	Entity* entity;
};

#endif
