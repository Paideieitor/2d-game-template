#include "Render.h"

#include "Window.h"
#include "Input.h"
#include "SceneManager.h"
#include "Textures.h"

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

void Render::AddRectangleEvent(int layer, fpoint position, int width, int height, Color color, bool usescale, float speed, bool filled)
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

	if (InCamera((int)position.x, (int)position.y, width, height) || !usescale)
		eventlist.insert(make_pair(layer, event));
}

void Render::AddLineEvent(int layer, fpoint firstPosition, fpoint secondPosition, Color color)
{
	RenderEvent event;

	event.type = LINE;

	event.position = firstPosition;
	event.secondPosition = secondPosition;

	event.color = color;

	eventlist.insert(make_pair(layer, event));
}

void Render::AddTextureEvent(int layer, Texture* texture, fpoint position, int x, int y, ipoint size, bool flip, int alpha, bool usescale, float speed, double angle, fpoint pivot)
{
	RenderEvent event;

	event.type = TEXTURE;

	event.texture = texture->texture;
	event.position = position;

	event.x = x;
	event.y = y;
	event.width = size.x;
	event.height = size.y;

	event.color = { 0,0,0,(unsigned int)alpha };

	event.speed = speed;

	event.flip = flip;
	event.usescale = usescale;

	event.angle = angle;
	event.pivot = pivot;
	
	if (InCamera((int)position.x, (int)position.y, size.x, size.y) || !usescale)
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
			DrawLine(event.position, event.secondPosition, event.color);
			break;
		case CIRCLE:
			DrawCircle(event.position, event.radius, event.color);
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
	const float scale = game->window->GetScale();

	SDL_Rect section = { x,y,width,height };

	SDL_Rect rect;

	rect.w = width;
	rect.h = height;

	if (usescale)
	{
		rect.x = (int)(camera.x * speed + position.x * scale);
		rect.y = (int)(camera.y * speed + position.y * scale);
		rect.w = (int)(rect.w * scale);
		rect.h = (int)(rect.h * scale);
	}
	else
	{
		rect.x = (int)position.x;
		rect.y = (int)position.y;
	}

	SDL_SetTextureAlphaMod(texture, (Uint8)alpha);

	SDL_Point p;
	
	p.x = (int)pivot.x;
	p.y = (int)pivot.y;

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

bool Render::DrawRect(fpoint position, int width, int height, Color color, bool usescale, bool filled) const
{
	const float scale = game->window->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int x = (int)position.x;
	int y = (int)position.y;

	if (usescale)
	{
		x = (int)(camera.x + x * scale);
		y = (int)(camera.y + y * scale);
		width = (int)(width * scale);
		height = (int)(height * scale);
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

bool Render::DrawLine(fpoint firstPosition, fpoint secondPosition, Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, firstPosition.x, firstPosition.y, secondPosition.x, secondPosition.y);
	return false;
}

bool Render::DrawCircle(fpoint position, int radius, Color color)
{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_SetRenderDrawColor(renderer, 223, 223, 223, 255);
		const int32_t diameter = (radius * 2);

		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, position.x + x, position.y - y);
			SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
			SDL_RenderDrawPoint(renderer, position.x - x, position.y - y);
			SDL_RenderDrawPoint(renderer, position.x - x, position.y + y);
			SDL_RenderDrawPoint(renderer, position.x + y, position.y - x);
			SDL_RenderDrawPoint(renderer, position.x + y, position.y + x);
			SDL_RenderDrawPoint(renderer, position.x - y, position.y - x);
			SDL_RenderDrawPoint(renderer, position.x - y, position.y + x);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
		return true;
}

bool Render::InCamera(int x, int y, int width, int height)
{
	const float scale = game->window->GetScale();

	SDL_Rect cull = camera;
	cull.x = (int)(cull.x / -scale);
	cull.y = (int)(cull.y / -scale);
	cull.w = (int)(cull.w / scale);
	cull.h = (int)(cull.h / scale);

	if (cull.x <= x + width && cull.x + cull.w >= x &&
		cull.y <= y + height && cull.h + cull.y >= y)
		return true;

	return false;
}