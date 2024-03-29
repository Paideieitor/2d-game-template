#include "Render.h"

#include "Window.h"
#include "Input.h"
#include "SceneManager.h"
#include "Textures.h"

#include "SDL/include/SDL_render.h"

Render::Render()
{
	name = "render";
	background = Color::black;
}

Render::~Render()
{

}

bool Render::SetUp(pugi::xml_node& node)
{
	resolution.x = node.attribute("width").as_int();
	resolution.y = node.attribute("height").as_int();

	vsync = node.child("vsync").attribute("value").as_bool();

	this->node = node;

	CreateRenderer();

	camera = new SDL_Rect{ 0,0, resolution.x, resolution.y };

	return true;
}

bool Render::Start()
{
	return true;
}

bool Render::Update(float dt)
{
	SDL_RenderClear(renderer);
	//FIRST ^

	/*
	if (game->input->CheckState(Key::W) == Input::State::REPEAT)
		(*camera).y++;
	if (game->input->CheckState(Key::S) == Input::State::REPEAT)
		(*camera).y--;
	if (game->input->CheckState(Key::A) == Input::State::REPEAT)
		(*camera).x++;
	if (game->input->CheckState(Key::D) == Input::State::REPEAT)
		(*camera).x--;
	*/
	PrintEvents();

	//LAST v
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
	SDL_RenderPresent(renderer);

	return true;
}

bool Render::CleanUp()
{
	SDL_DestroyRenderer(renderer);

	delete camera;

	return true;
}

void Render::RenderRectangle(bool ui, int layer, const fpoint& position, int width, int height, const Color& color, bool usescale, float speed, bool filled)
{
	Render::Event event;

	event.type = Type::RECTANGLE;

	event.position = position;
	event.width = width;
	event.height = height;

	event.color = color;

	event.speed = speed;

	event.usescale = usescale;
	event.filled = filled;

	if (ui)
	{
		uieventlist.insert(std::make_pair(layer, event));
		return;
	}

	if (InCamera((int)position.x, (int)position.y, width, height) || !usescale)
		eventlist.insert(std::make_pair(layer, event));
}

void Render::RenderTexture(bool ui, int layer, TexturePtr texture, const fpoint& position, int x, int y, const ipoint& size, bool flip, int alpha, bool usescale, float speed, double angle, const fpoint& pivot)
{
	Render::Event event;

	event.type = Type::TEXTURE;

	event.texture = texture;
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

	if (ui)
	{
		uieventlist.insert(std::make_pair(layer, event));
		return;
	}
	
	if (InCamera((int)position.x, (int)position.y, size.x, size.y) || !usescale)
		eventlist.insert(std::make_pair(layer, event));
}

void Render::RenderCircle(bool ui, int layer, const fpoint& center, int radius, const Color& color, bool usescale, float speed)
{
	Render::Event event;

	event.type = Type::CIRCLE;

	event.position = center;
	event.radius = radius;

	event.color = color;

	event.speed = speed;
	event.usescale = usescale;

	if (ui)
	{
		uieventlist.insert(std::make_pair(layer, event));
		return;
	}

	eventlist.insert(std::make_pair(layer, event));
}

void Render::RenderLine(bool ui, int layer, const fpoint& startpoint, const fpoint& endpoint, const Color& color, bool usescale, float speed)
{
	Render::Event event;

	event.type = Type::LINE;

	event.position = startpoint;
	event.endpoint = endpoint;

	event.color = color;
	
	event.speed = speed;
	event.usescale = usescale;

	if (ui)
	{
		uieventlist.insert(std::make_pair(layer, event));
		return;
	}

	eventlist.insert(std::make_pair(layer, event));
}

const ipoint Render::GetCameraPosition()
{
	return ipoint(-camera->x, -camera->y);
}

void Render::SetCameraPosition(ipoint position)
{
	camera->x = position.x;
	camera->y = position.y;
}

void Render::SetVsync(bool enable)
{
	if (vsync == enable)
		return;
	SDL_DestroyRenderer(renderer);

	vsync = enable;
	CreateRenderer();

	node.child("vsync").attribute("value").set_value(vsync);
	game->document.save_file("config.xml");
}

bool Render::CreateRenderer()
{
	Uint32 flags = SDL_RENDERER_ACCELERATED;
	if (vsync == true)
		flags |= SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer(game->window->window, -1, flags);
	if (renderer == NULL)
	{
		game->Log("Renderer -> Bad Thing, Renderer Error: " + std::string(SDL_GetError()));
		return false;
	}
	SDL_RenderSetLogicalSize(renderer, resolution.x, resolution.y);

	return true;
}

void Render::PrintEvents()
{
	SDL_RenderSetLogicalSize(renderer, resolution.x, resolution.y);

	for (std::map<int, Render::Event>::iterator e = eventlist.begin(); e != eventlist.end(); e++)
	{
		Render::Event event = e->second;
		switch (event.type)
		{
		case Type::RECTANGLE:
			DrawRect(event.position, event.width, event.height, event.color, event.usescale, event.filled);
			break;
		case Type::LINE:
			DrawLine(event.position, event.endpoint, event.color, event.usescale, event.speed);
			break;
		case Type::CIRCLE:
			DrawCircle(event.position, event.radius, event.color, event.usescale, event.speed);
			break;
		case Type::TEXTURE:
			DrawTexture(event.texture, event.position, event.x, event.y, event.width, event.height, event.flip, event.color.a, event.usescale, event.speed, event.angle, event.pivot);
			break;
		}
	}
	eventlist.erase(eventlist.begin(), eventlist.end());

	SDL_RenderSetLogicalSize(renderer, uiresolution.x, uiresolution.y);

	for (std::map<int, Render::Event>::iterator e = uieventlist.begin(); e != uieventlist.end(); e++)
	{
		Render::Event event = e->second;
		switch (event.type)
		{
		case Type::RECTANGLE:
			DrawRect(event.position, event.width, event.height, event.color, event.usescale, event.filled);
			break;
		case Type::LINE:
			DrawLine(event.position, event.endpoint, event.color, event.usescale, event.speed);
			break;
		case Type::CIRCLE:
			DrawCircle(event.position, event.radius, event.color, event.usescale, event.speed);
			break;
		case Type::TEXTURE:
			DrawTexture(event.texture, event.position, event.x, event.y, event.width, event.height, event.flip, event.color.a, event.usescale, event.speed, event.angle, event.pivot);
			break;
		}
	}
	uieventlist.erase(uieventlist.begin(), uieventlist.end());
}

void Render::ClearEvents()
{
	eventlist.erase(eventlist.begin(), eventlist.end());
}

bool Render::DrawTexture(TexturePtr texture, const fpoint& position, int x, int y, int width, int height, bool flip, int alpha, bool worldposition, float speed, double angle, const fpoint& pivot)
{
	SDL_Rect section = { x,y,width,height };

	SDL_Rect rect;

	rect.w = width;
	rect.h = height;

	if (worldposition)
	{
		rect.x = (int)((*camera).x * speed + position.x);
		rect.y = (int)((*camera).y * speed + position.y);
		rect.w = (int)(rect.w);
		rect.h = (int)(rect.h);
	}
	else
	{
		rect.x = (int)position.x;
		rect.y = (int)position.y;
	}

	SDL_SetTextureAlphaMod(texture->texture, (Uint8)alpha);

	SDL_Point p;
	
	p.x = (int)pivot.x;
	p.y = (int)pivot.y;

	SDL_RendererFlip f = SDL_FLIP_NONE;
	if (flip)
		f = SDL_FLIP_HORIZONTAL;

	if (SDL_RenderCopyEx(renderer, texture->texture, &section, &rect, angle, &p, f) != 0)
	{
		game->Log("Draw Texture -> Bad Thing, Error: " + std::string(SDL_GetError()));
		return false;
	}

	return true;
}

bool Render::DrawRect(const fpoint& position, int width, int height, const Color& color, bool worldposition, bool filled) const
{
	int x = (int)position.x;
	int y = (int)position.y;

	if (worldposition)
	{
		x = (int)((*camera).x + x);
		y = (int)((*camera).y + y);
		width = (int)(width);
		height = (int)(height);
	}

	SDL_Rect rect = { x, y, width, height };

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int result;
	if (filled)
		result = SDL_RenderFillRect(renderer, &rect);
	else
		result = SDL_RenderDrawRect(renderer, &rect);

	if (result != 0)
	{
		game->Log("Draw Rectangle -> Bad Thing, Error: " + std::string(SDL_GetError()));
		return false;
	}

	return true;
}

bool Render::DrawCircle(fpoint& position, int radius, const Color& color, bool worldposition, float speed)
{
	if (worldposition)
	{
		position.x = ((*camera).x + position.x);
		position.y = ((*camera).y + position.y);
	}

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	const int diameter = (radius * 2);

	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, (int)position.x + x, (int)position.y - y);
		SDL_RenderDrawPoint(renderer, (int)position.x + x, (int)position.y + y);
		SDL_RenderDrawPoint(renderer, (int)position.x - x, (int)position.y - y);
		SDL_RenderDrawPoint(renderer, (int)position.x - x, (int)position.y + y);
		SDL_RenderDrawPoint(renderer, (int)position.x + y, (int)position.y - x);
		SDL_RenderDrawPoint(renderer, (int)position.x + y, (int)position.y + x);
		SDL_RenderDrawPoint(renderer, (int)position.x - y, (int)position.y - x);
		SDL_RenderDrawPoint(renderer, (int)position.x - y, (int)position.y + x);

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

bool Render::DrawLine(fpoint& firstPosition, fpoint& secondPosition, const Color& color, bool worldposition, float speed)
{
	if (worldposition)
	{
		firstPosition.x = ((*camera).x + firstPosition.x);
		firstPosition.y = ((*camera).y + firstPosition.y);

		secondPosition.x = ((*camera).x + secondPosition.x);
		secondPosition.y = ((*camera).y + secondPosition.y);
	}

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, (int)firstPosition.x, (int)firstPosition.y, (int)secondPosition.x, (int)secondPosition.y);

	return false;
}

bool Render::InCamera(int x, int y, int width, int height)
{
	SDL_Rect cull = (*camera);
	cull.x = (int)(-cull.x);
	cull.y = (int)(-cull.y);
	cull.w = (int)(cull.w);
	cull.h = (int)(cull.h);

	if (cull.x <= x + width && cull.x + cull.w >= x &&
		cull.y <= y + height && cull.h + cull.y >= y)
		return true;

	return false;
}