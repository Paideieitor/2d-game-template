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
		fpoint secondPosition;

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

	void RenderRectangle(int layer, fpoint position, ipoint size, Color color, bool usescale = true, float speed = 1.0f, bool filled = true)
	{
		RenderRectangle(layer, position, size.x, size.y, color, usescale, speed, filled);
	}
	void RenderRectangle(int layer, fpoint position, int width, int height, Color color, bool usescale = true, float speed = 1.0f, bool filled = true);
	void RenderCircle(int layer, fpoint center, int r, Color color, bool usescale = false, float speed = 1.0f, bool filled = true) {}
	void RenderTexture(int layer, TexturePtr texture, fpoint position, int x, int y, ipoint size, bool flip = false, int alpha = 255, bool usescale = true, float speed = 1.0f, double angle = 0, fpoint pivot = {0,0});

	void AddLineEvent(int layer, fpoint firstPosition, fpoint secondPosition, Color color);

	void ClearEvents();

	ipoint GetCameraPosition(bool worldposition = false);

	Renderer* renderer;

	Rect* camera;
	Rect* viewport;

	ipoint resolution;

private:

	void PrintEvents();

	bool DrawRect(fpoint position, int width, int height, Color color, bool usescale, bool filled) const;
	bool DrawLine(fpoint firstPosition, fpoint secondPosition, Color color);
	bool DrawCircle(fpoint position, int radius, Color color);
	bool DrawTexture(TexturePtr texture, fpoint position, int x, int y, int width, int height, bool flip, int alpha, bool usescale, float speed, double angle, fpoint pivot);

	bool InCamera(int x, int y, int width, int height);

	std::multimap<int, Render::Event> eventlist;
};

#endif
