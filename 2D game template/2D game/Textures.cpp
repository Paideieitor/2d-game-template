#include "Textures.h"

#include "AssetManager.h"
#include "Render.h"

#include "IMG/include/SDL_image.h"
#pragma comment( lib, "IMG/lib/SDL2_image.lib" )

Texture::Texture(const std::string& path, TextureData* texture) : path(path), texture(texture), font(nullptr), color()
{
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

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
		game->Log("Texture -> Bad Thing, Error: Couldn't Init");
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
	for (size_t i = 0; i < textures.size(); ++i)
		if (textures[i].use_count() <= 1)
			textures.erase(textures.begin() + i);

	return true;
}

bool Textures::CleanUp()
{
	textures.clear();
	return true;
}

TexturePtr Textures::Load(const std::string& path)
{
	for (size_t i = 0; i < textures.size(); ++i)
		if (textures[i]->path == path)
			return textures[i];

	char* buffer;
	SDL_Surface* surface = IMG_Load_RW(game->assets->Load(path, &buffer), 1);
	delete buffer;

	SDL_Texture* texture = nullptr;
	if (surface == NULL)
	{
		game->Log("Texture surface loading -> Bad Thing, Error in " + path + " -> " + std::string(SDL_GetError()));
		return nullptr;
	}

	texture = SurfaceToTexture(surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr)
		return nullptr;

	TexturePtr output = std::make_shared<Texture>(path, texture);
	textures.push_back(output);

	return output;
}

TexturePtr Textures::LoadText(FontPtr font, const std::string& text, Color color)
{
	if (!font)
		return nullptr;

	for (size_t i = 0; i < textures.size(); ++i)
		if (textures[i]->path == text && textures[i]->font == font && textures[i]->color == color)
			return textures[i];

	SDL_Surface* surface = game->fonts->TextToSurface(font->font, text, color);
	
	SDL_Texture* texture = nullptr;
	if (surface == NULL)
	{
		game->Log("Texture font surface -> Bad Thing, Error in " + text + " -> " + std::string(SDL_GetError()));
		return nullptr;

	}

	texture = game->textures->SurfaceToTexture(surface);
	SDL_FreeSurface(surface);
	if (!texture)
		return nullptr;

	TexturePtr output = std::make_shared<Texture>(text, texture);
	textures.push_back(output);

	output->font = font;
	output->color = color;

	return output;
}

TextureData* Textures::SurfaceToTexture(Surface* surface)
{
	SDL_Texture* output = SDL_CreateTextureFromSurface(game->render->renderer, surface);
	if (output == NULL)
	{
		game->Log("Texture texture creation -> Bad Thing, Error:" + std::string(SDL_GetError()));
		return nullptr;
	}

	return output;
}
