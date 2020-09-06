#include "Fonts.h"

#include "AssetManager.h"
#include "Textures.h"

Fonts::Fonts()
{
	name = "fonts";
}

Fonts::~Fonts()
{
	TTF_Quit();
}

bool Fonts::SetUp(pugi::xml_node&)
{
	return true;
}

bool Fonts::Start()
{
	TTF_Init();

	return true;
}

bool Fonts::Update(float dt)
{
	return true;
}

bool Fonts::CleanUp()
{
	while (fonts.size() != 0)
	{
		delete *fonts.begin();
		fonts.erase(fonts.begin());
	}

	return true;
}

TTF_Font* Fonts::Load(const char* path, int size)
{
	char* buffer;
	TTF_Font* output = TTF_OpenFontRW(game->assets->Load(path, &buffer), 1, size);

	if (!output)
	{
		cout << "Loading font -> Bad Thing, Error in " << path << " -> " << SDL_GetError() << endl;
		return output;
	}

	fonts.push_back(new Font(buffer, output));

	return output;
}

SDL_Texture* Fonts::GetTextTexture(TTF_Font* font, const char* text, color color)
{
	SDL_Texture* output = nullptr;

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color.ToSDL());

	output = game->textures->SurfaceToTexture(surface);
	SDL_FreeSurface(surface);

	return output;
}