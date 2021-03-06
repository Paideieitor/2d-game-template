#include "Render.h"

#include "Window.h"
#include "Input.h"
#include "SceneManager.h"

Render::Render()
{
	name = "render";
}
Render::~Render()
{

}

bool Render::SetUp(pugi::xml_node& node)
{
	resolution.x = node.attribute("width").as_int();
	resolution.y = node.attribute("height").as_int();

	Uint32 flags = SDL_RENDERER_ACCELERATED;
	if (node.child("vsync").attribute("value").as_bool() == true)
		flags |= SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer(game->window->window, -1, flags);
	if (renderer == NULL)
	{
		cout << "Renderer -> Bad Thing, Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		camera = { 0,0, resolution.x, resolution.y };
		SDL_RenderSetLogicalSize(renderer, resolution.x, resolution.y);
	}

	return true;
}

bool Render::Start()
{
	SDL_RenderGetViewport(renderer, &viewport);

	return true;
}

bool Render::Update(float dt)
{
	SDL_RenderClear(renderer);
	//FIRST ^

	//if (game->input->GetKey(SDL_SCANCODE_W) == REPEAT)
	//	camera.y++;
	//if (game->input->GetKey(SDL_SCANCODE_S) == REPEAT)
	//	camera.y--;
	//if (game->input->GetKey(SDL_SCANCODE_A) == REPEAT)
	//	camera.x++;
	//if (game->input->GetKey(SDL_SCANCODE_D) == REPEAT)
	//	camera.x--;
	//if (game->input->GetKey(SDL_SCANCODE_Q) == DOWN)
	//	cout << "camera -> x: " << -camera.x << " y: " << -camera.y << endl;
	//if (game->input->GetButton(1) == DOWN)
	//	cout << "mouse -> x: " << -camera.x + game->input->GetMousePos().x << " y: " << -camera.y + game->input->GetMousePos().y << endl;

	PrintEvents();

	//LAST v
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);

	return true;
}

bool Render::CleanUp()
{
	return true;
}

void Render::AddRectangleEvent(int layer, fpoint position, int width, int height, color color, bool usescale, float speed, bool filled)
{
	RenderEvent event;

	event.type = RECTANGLE;

	event.position = position;
	event.width = width;
	event.height = height;

	event.color = color;

	event.speed = speed;

	event.usescale = usescale;
	event.filled = filled;

	if (InCamera(position.x, position.y, width, height) || !usescale)
		eventlist.insert(make_pair(layer, event));
}

void Render::AddTextureEvent(int layer, SDL_Texture* texture, fpoint position, int x, int y, int width, int height, bool flip, int alpha, bool usescale, float speed, double angle, fpoint pivot)
{
	RenderEvent event;

	event.type = TEXTURE;

	event.texture = texture;
	event.position = position;

	event.x = x;
	event.y = y;
	event.width = width;
	event.height = height;

	event.color = { 0,0,0,(unsigned int)alpha };

	event.speed = speed;

	event.flip = flip;
	event.usescale = usescale;

	event.angle = angle;
	event.pivot = pivot;
	
	if (InCamera((int)position.x, (int)position.y, width, height) || !usescale)
		eventlist.insert(make_pair(layer, event));
}

void Render::PrintEvents()
{
	for (map<int, RenderEvent>::iterator e = eventlist.begin(); e != eventlist.end(); e++)
	{
		RenderEvent event = e->second;
		switch (event.type)
		{
		case RECTANGLE:
			DrawRect(event.position, event.width, event.height, event.color, event.usescale, event.filled);
			break;
		case LINE:
			break;
		case CIRCLE:
			break;
		case TEXTURE:
			DrawTexture(event.texture, event.position, event.x, event.y, event.width, event.height, event.flip, event.color.a, event.usescale, event.speed, event.angle, event.pivot);
			break;
		}
	}

	eventlist.erase(eventlist.begin(), eventlist.end());
}

void Render::ClearEvents()
{
	eventlist.erase(eventlist.begin(), eventlist.end());
}

bool Render::DrawTexture(SDL_Texture* texture, fpoint position, int x, int y, int width, int height, bool flip, int alpha, bool usescale, float speed, double angle, fpoint pivot)
{
	float scale = game->window->scale;

	SDL_Rect section = { x,y,width,height };

	SDL_Rect rect;

	rect.w = width;
	rect.h = height;

	if (usescale)
	{
		rect.x = camera.x * speed + position.x * scale;
		rect.y = camera.y * speed + position.y * scale;
		rect.w *= scale;
		rect.h *= scale;
	}
	else
	{
		rect.x = position.x;
		rect.y = position.y;
	}

	SDL_SetTextureAlphaMod(texture, alpha);

	SDL_Point p;
	
	p.x = pivot.x;
	p.y = pivot.y;


	SDL_RendererFlip f = SDL_FLIP_NONE;
	if (flip)
		f = SDL_FLIP_HORIZONTAL;

	if (SDL_RenderCopyEx(renderer, texture, &section, &rect, angle, &p, f) != 0)
	{
		cout << "Draw Texture -> Bad Thing, Error: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}

bool Render::DrawRect(fpoint position, int width, int height, color color, bool usescale, bool filled) const
{
	float scale = game->window->scale;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int x = (int)position.x;
	int y = (int)position.y;

	if (usescale)
	{
		x = (int)(camera.x + x * scale);
		y = (int)(camera.y + y * scale);
		width *= scale;
		height *= scale;
	}

	SDL_Rect rect = { x, y, width, height };

	int result;
	if (filled)
		result = SDL_RenderFillRect(renderer, &rect);
	else
		result = SDL_RenderDrawRect(renderer, &rect);

	if (result != 0)
	{
		cout << "Draw Rectangle -> Bad Thing, Error: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}

bool Render::InCamera(int x, int y, int width, int height)
{
	float scale = game->window->scale;

	SDL_Rect cull = camera;
	cull.x /= -scale;
	cull.y /= -scale;
	cull.w /= scale;
	cull.h /= scale;

	if (cull.x <= x + width && cull.x + cull.w >= x &&
		cull.y <= y + height && cull.h + cull.y >= y)
		return true;

	return false;
}