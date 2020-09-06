#ifndef RENDER_H
#define RENDER_H

#include "Module.h"
#include <map>

enum rendertype
{
	RECTANGLE,
	LINE,
	CIRCLE,
	TEXTURE
};

struct RenderEvent
{
	rendertype type;

	SDL_Texture* texture;

	fpoint position;

	int x;
	int y;
	int width;
	int height;

	color color;

	float speed;

	bool flip;
	bool usescale;
	bool filled;

	double angle;
	fpoint pivot;
};

class Render : public Module
{
public:

	Render();
	virtual ~Render();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void AddRectangleEvent(int layer, fpoint position, int width, int height, color color, bool usescale = true, float speed = 1.0f, bool filled = true);
	void AddCircleEvent(int layer, fpoint center, int r, color color, bool usescale = false, float speed = 1.0f, bool filled = true) {}
	void AddTextureEvent(int layer, SDL_Texture* texture, fpoint position, int x, int y, int width, int height, bool flip = false, int alpha = 255, bool usescale = true, float speed = 1.0f, double angle = 0, fpoint pivot = {0,0});

	void ClearEvents();

	SDL_Renderer* renderer;

	SDL_Rect camera;
	SDL_Rect viewport;

	ipoint resolution;

private:

	void PrintEvents();

	bool DrawRect(fpoint position, int width, int height, color color, bool usescale, bool filled) const;
	bool DrawTexture(SDL_Texture* texture, fpoint position, int x, int y, int width, int height, bool flip, int alpha, bool usescale, float speed, double angle, fpoint pivot);

	bool InCamera(int x, int y, int width, int height);

	multimap<int, RenderEvent> eventlist;
};

#endif
