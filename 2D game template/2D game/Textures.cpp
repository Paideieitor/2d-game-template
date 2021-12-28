#include "Textures.h"

#include "IMG/include/SDL_image.h"
#pragma comment( lib, "IMG/lib/SDL2_image.lib" )

#include "AssetManager.h"
#include "Render.h"

Textures::Textures()
{
	name = "textures";
}

Textures::~Textures()
{
	IMG_Quit();
}

bool Textures::SetUp(pugi::xml_node&)
{
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		cout << "Texture -> Bad Thing, Error: Couldn't Init" << endl;
		return false;
	}

	return true;
}

bool Textures::Start()
{
	return true;
}

bool Textures::Update(float dt)
{
	return true;
}

bool Textures::CleanUp()
{
	while (textures.size() != 0)
	{
		delete* textures.begin();
		textures.erase(textures.begin());
	}

	return true;
}

Texture* Textures::Load(const char* path)
{
	for (vector<Texture*>::iterator t = textures.begin(); t != textures.end(); t++)
	{
		if ((*t)->path == path)
		{
			++(*t)->instances;
			return *t;
		}
	}

	char* buffer;
	SDL_Surface* surface = IMG_Load_RW(game->assets->Load(path, &buffer), 1);
	delete buffer;

	SDL_Texture* texture = nullptr;
	if (surface != NULL)
	{
		texture = SurfaceToTexture(surface);
		SDL_FreeSurface(surface);

		if (texture == nullptr)
			return nullptr;
	}
	else
	{
		cout << "Texture surface loading -> Bad Thing, Error in " << path << " -> " << SDL_GetError() << endl;
		return nullptr;
	}

	Texture* output = new Texture(path, texture);
	textures.push_back(output);
	++output->instances;

	return output;
}

Texture* Textures::LoadText(Font* font, const char* text, Color color)
{
	if (!font)
		return nullptr;

	for (vector<Texture*>::iterator t = textures.begin(); t != textures.end(); t++)
	{
		if ((*t)->path == text && (*t)->font == font && (*t)->color == color)
		{
			++(*t)->instances;
			return *t;
		}
	}

	SDL_Surface* surface = game->fonts->TextToSurface(font->font, text, color);
	
	SDL_Texture* texture = nullptr;
	if (surface != NULL)
	{
		texture = game->textures->SurfaceToTexture(surface);
		SDL_FreeSurface(surface);
	}
	else
	{
		 cout << "Texture font surface -> Bad Thing, Error in " << text << " -> " << SDL_GetError() << endl;
		 return nullptr;
	}
	
	if (!texture)
		return nullptr;

	Texture* output = new Texture(text, texture);
	textures.push_back(output);
	++output->instances;
	output->font = font;
	output->color = color;

	return output;
}

void Textures::Unload(Texture*& texture)
{
	for (vector<Texture*>::iterator t = textures.begin(); t != textures.end(); t++)
	{
		if (*t == texture)
		{
			--(*t)->instances;
			if ((*t)->instances <= 0)
			{
				delete texture;
				textures.erase(t);

				texture = nullptr;
			}

			break;
		}
	}
}

SDL_Texture* Textures::SurfaceToTexture(SDL_Surface* surface)
{
	SDL_Texture* output = SDL_CreateTextureFromSurface(game->render->renderer, surface);
	if (output == NULL)
	{
		cout << "Texture texture creation -> Bad Thing, Error:" << SDL_GetError() << endl;
		return nullptr;
	}

	return output;
}

void Textures::ChangeTexture(Texture*& source, Texture*& destination)
{
	Unload(destination);

	++source->instances;
	destination = source;
}
