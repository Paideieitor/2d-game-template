#ifndef UIELEMENTS_H
#define UIELEMENTS_H

#define UI_RENDER_LAYER 5

#include "Game.h"

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

	enum class Output
	{
		NO_MODIFY,		// the ui manager list was NOT modified
		LIST_MODIFY,	// the ui manager list was modified
		ERROR
	};

	enum class State
	{
		IDLE,
		HOVER,
		CLICK,
		DISABLED
	};

public:

	UIElement(const Type& type, const fpoint& position, bool worldposition, const Observer& observer);
	virtual ~UIElement();

	virtual Output Update(float dt) = 0;
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

	bool IsDisabled() { return state == State::DISABLED; }
	void Disable(bool disable) { disable ? state = State::DISABLED : state = State::IDLE; }

public:

	const Type type;

protected:

	virtual void ActiveChanged() = 0;
	virtual void PositionChanged() = 0;
	virtual void SizeChanged() = 0;
	virtual void WorldPosChanged() = 0;

protected:

	State state;

	Observer observer;

private:

	bool active;

	fpoint position;
	ipoint size;
	bool worldposition;
};

struct UIStateTextures
{
public:

	UIStateTextures() : idle(nullptr), hover(nullptr), click(nullptr), disabled(nullptr) {}
	UIStateTextures(TexturePtr idle, TexturePtr hover = nullptr, TexturePtr click = nullptr, TexturePtr disabled = nullptr)
		: idle(idle), hover(hover), click(click), disabled(disabled) {}

	// Not called on destructor
	void UnloadTextures();

	TexturePtr const GetTexture(UIElement::State state) const
	{
		switch (state)
		{
		case UIElement::State::IDLE:
			return idle;
			break;
		case UIElement::State::HOVER:
			return hover ? hover : idle;
			break;
		case UIElement::State::CLICK:
			return click ? click : idle;
			break;
		case UIElement::State::DISABLED:
			return disabled ? disabled : idle;
			break;
		}
		return nullptr;
	}

private:

	TexturePtr idle;
	TexturePtr hover;
	TexturePtr click;
	TexturePtr disabled;
};

#endif
