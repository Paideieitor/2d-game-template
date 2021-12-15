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

Font* Fonts::Load(const char* path, int size)
{
	char* buffer = nullptr;
	TTF_Font* font = TTF_OpenFontRW(game->assets->Load(path, &buffer), 1, size);

	if (!font)
	{
		cout << "Loading font -> Bad Thing, Error in " << path << " -> " << SDL_GetError() << endl;
		return nullptr;
	}

	Font* output = new Font(buffer, font);
	fonts.push_back(output);

	return output;
}

SDL_Surface* Fonts::TextToSurface(TTF_Font* font, const char* text, Color color)
{
	return TTF_RenderText_Solid(font, text, color.ToSDL());
}
