#ifndef UIELEMENTS_H
#define UIELEMENTS_H

#define UI_RENDER_LAYER 5

#include "Game.h"

#include "Animation.h"
#include "Observer.h"

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;
class Font;
typedef std::shared_ptr<Font> FontPtr;

class UIElement
{
public:

	enum class Type
	{
		BUTTON,
		BUTTONARRAY,
		SCROLLBAR,
		LABEL,
		INPUTBOX
	};

	enum class State
	{
		IDLE,
		HOVER,
		CLICK
	};

public:

	UIElement(const Type& type, const fpoint& position, bool worldposition, const Observer& observer);
	virtual ~UIElement();

	virtual bool Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void UIEvent(UIElement*) {}

	const bool IsActive() { return active; }
	void SetActive(bool active)
	{
		this->active = active;
		ActiveChanged();
	}

	const fpoint GetPosition() const { return position; }
	void SetPosition(const fpoint& position) { SetPosition(position.x, position.y); }
	void SetPosition(float x, float y)
	{
		position = { x,y };
		PositionChanged();
	}

	const ipoint GetSize() const { return size; }
	void SetSize(const ipoint& size) { SetSize(size.x, size.y); }
	void SetSize(int w, int h)
	{ 
		size = { w,h }; 
		SizeChanged();
	}

	const bool IsWorldPos() const { return worldposition; }
	void EnableWorldPos(bool enable) 
	{
		worldposition = enable;
		WorldPosChanged();
	}

	bool IsIdle() { return state == State::IDLE; }
	void SetIdle() { state = State::IDLE; }

	bool IsClicked() { return state == State::CLICK; }
	void SetClicked() { state = State::CLICK; }

	bool IsHovered() { return state == State::HOVER; }
	void SetHover() { state = State::HOVER; }

	bool IsDisabled() { return disabled; }
	void Disable(bool disable) 
	{ 
		disabled = disable; 
		DisableChanged(); 
	}

public:

	const Type type;

protected:

	virtual void ActiveChanged() = 0;
	virtual void DisableChanged() = 0;
	virtual void PositionChanged() = 0;
	virtual void SizeChanged() = 0;
	virtual void WorldPosChanged() = 0;

protected:

	State state;

	Observer observer;

private:

	bool active;
	bool disabled;

	fpoint position;
	ipoint size;
	bool worldposition;
};

struct UIGraphics
{
public:

	UIGraphics() : texture(nullptr), idle(nullptr), hover(nullptr), click(nullptr), disabled(nullptr) {}
	UIGraphics(const TexturePtr& texture, const Animation& idle, const Animation& hover = nullptr, const Animation& click = nullptr, 
		const Animation& disabled = nullptr)
		: texture(texture), idle(idle), hover(hover != nullptr ? hover : idle), click(click != nullptr ? click : idle), 
		disabled(disabled != nullptr ? disabled : idle) 
	{}

	TexturePtr texture;

	Animation idle;
	Animation hover;
	Animation click;
	Animation disabled;
};

#endif
