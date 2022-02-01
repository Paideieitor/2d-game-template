#ifndef RENDER_H
#define RENDER_H

#include "Module.h"

#include "Frame.h"

#include <map>

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

typedef struct SDL_Renderer Renderer;
typedef struct SDL_Rect Rect;

class Render : public Module
{
private:

	enum class Type
	{
		RECTANGLE,
		LINE,
		CIRCLE,
		TEXTURE
	};

	struct Event
	{
		Render::Type type;

		TexturePtr texture;

		fpoint position;
		fpoint endpoint;

		int radius;
		int x;
		int y;
		int width;
		int height;

		Color color;

		float speed;

		bool flip;
		bool usescale;
		bool filled;

		double angle;
		fpoint pivot;
	};

public:

	Render();
	virtual ~Render();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void RenderRectangle(bool ui, int layer, const fpoint& position, const ipoint& size, const Color& color, bool usescale = true, 
		float speed = 1.0f, bool filled = true)
	{
		RenderRectangle(ui, layer, position, size.x, size.y, color, usescale, speed, filled);
	}
	void RenderRectangle(bool ui, int layer, const fpoint& position, int width, int height, const Color& color, bool usescale = true,
		float speed = 1.0f, bool filled = true);
	void RenderTexture(bool ui, int layer, TexturePtr texture, const fpoint& position, const Frame& frame, bool flip = false, int alpha = 255,
		bool usescale = true, float speed = 1.0f, double angle = 0, const fpoint& pivot = { 0,0 })
	{
		RenderTexture(ui, layer, texture, position, frame.position.x, frame.position.y, frame.size, flip, alpha, usescale, speed, angle, pivot);
	}
	void RenderTexture(bool ui, int layer, TexturePtr texture, const fpoint& position, int x, int y, const ipoint& size, bool flip = false, int alpha = 255,
		bool usescale = true, float speed = 1.0f, double angle = 0, const fpoint& pivot = {0,0});
	void RenderCircle(bool ui, int layer, const fpoint& center, int radius, const Color& color, bool usescale = false, float speed = 1.0f);
	void RenderLine(bool ui, int layer, const fpoint& startpoint, const fpoint& endpoint, const Color& color, bool usescale = false, float speed = 1.0f);

	const ipoint GetCameraPosition();
	void SetCameraPosition(ipoint position);
	const ipoint GetResolution(bool ui) { return ui ? uiresolution : resolution; }

	const bool UsingVsync() { return vsync; }
	void SetVsync(bool enable);

public:

	Color background;

private:

	bool CreateRenderer();

	void PrintEvents();
	void ClearEvents();

	bool DrawRect(const fpoint& position, int width, int height, const Color& color, bool worldposition, bool filled) const;
	bool DrawTexture(TexturePtr texture, const fpoint& position, int x, int y, int width, int height, bool flip, int alpha, bool worldposition,
		float speed, double angle, const fpoint& pivot);
	bool DrawCircle(fpoint& position, int radius, const Color& color, bool worldposition, float speed);
	bool DrawLine(fpoint& firstPosition, fpoint& secondPosition, const Color& color, bool worldposition, float speed);
	
	bool InCamera(int x, int y, int width, int height);

private:

	bool vsync;

	Renderer* renderer;

	Rect* camera;

	ipoint resolution;
	ipoint uiresolution = ipoint(1920, 1080);

	std::multimap<int, Render::Event> eventlist;
	std::multimap<int, Render::Event> uieventlist;

	pugi::xml_node node;

	friend class Textures;
};

#endif
