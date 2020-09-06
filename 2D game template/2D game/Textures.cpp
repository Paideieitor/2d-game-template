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

SDL_Texture* Textures::Load(const char* path)
{
	SDL_Texture* output = nullptr;

	for (vector<Texture*>::iterator t = textures.begin(); t != textures.end(); t++)
	{
		Texture* tex = *t;
		if (tex->path == path)
			return tex->texture;
	}

	char* buffer;
	SDL_Surface* surface = IMG_Load_RW(game->assets->Load(path, &buffer), 1);
	delete buffer;

	if (surface != NULL)
	{
		output = SurfaceToTexture(surface);
		SDL_FreeSurface(surface);
	}
	else
	{
		cout << "Texture surface loading -> Bad Thing, Error in " << path << " -> " << SDL_GetError() << endl;
		return nullptr;
	}

	textures.push_back(new Texture(path, output));

	return output;
}

SDL_Texture* Textures::LoadText(TTF_Font* font, const char* text, color color, ipoint& size)
{
	SDL_Texture* output;

	output = game->fonts->GetTextTexture(font, text, color);

	textures.push_back(new Texture(text, output));

	size = game->textures->GetTextureSize(output);

	return output;
}

void Textures::Unload(SDL_Texture* texture)
{
	for (vector<Texture*>::iterator t = textures.begin(); t != textures.end(); t++)
	{
		Texture* tex = *t;
		if (tex->texture == texture)
		{
			delete tex;
			textures.erase(t);

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

ipoint Textures::GetTextureSize(SDL_Texture* texture)
{
	ipoint output;
	SDL_QueryTexture(texture, NULL, NULL, &output.x, &output.y);

	return output;
}
