#ifndef RENDER_H
#define RENDER_H

#include "Module.h"

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

	void RenderRectangle(int layer, const fpoint& position, const ipoint& size, const Color& color, bool usescale = true, 
		float speed = 1.0f, bool filled = true)
	{
		RenderRectangle(layer, position, size.x, size.y, color, usescale, speed, filled);
	}
	void RenderRectangle(int layer, const fpoint& position, int width, int height, const Color& color, bool usescale = true, 
		float speed = 1.0f, bool filled = true);
	void RenderCircle(int layer, const fpoint& center, int radius, const Color& color, bool usescale = false, float speed = 1.0f);
	void RenderTexture(int layer, TexturePtr texture, const fpoint& position, int x, int y, const ipoint& size, bool flip = false, int alpha = 255,
		bool usescale = true, float speed = 1.0f, double angle = 0, const fpoint& pivot = {0,0});
	void RenderLine(int layer, const fpoint& startpoint, const fpoint& endpoint, const Color& color);

	const ipoint GetCameraPosition(bool worldposition = false);
	const ipoint GetResolution() { return resolution; }

	const bool UsingVsync() { return vsync; }
	void SetVsync(bool enable);

public:

	Color background;

private:

	bool CreateRenderer();

	void PrintEvents();
	void ClearEvents();

	bool DrawRect(const fpoint& position, int width, int height, const Color& color, bool usescale, bool filled) const;
	bool DrawTexture(TexturePtr texture, const fpoint& position, int x, int y, int width, int height, bool flip, int alpha, bool usescale, 
		float speed, double angle, const fpoint& pivot);
	bool DrawCircle(const fpoint& position, int radius, const Color& color);
	bool DrawLine(const fpoint& firstPosition, const fpoint& secondPosition, const Color& color);
	
	bool InCamera(int x, int y, int width, int height);

private:

	bool vsync;

	Renderer* renderer;

	Rect* camera;
	Rect* viewport;

	ipoint resolution;

	std::multimap<int, Render::Event> eventlist;

	pugi::xml_node node;

	friend class Textures;
};

#endif
