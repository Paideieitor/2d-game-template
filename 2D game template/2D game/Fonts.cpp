#include "Fonts.h"

#include "AssetManager.h"
#include "Textures.h"

#include "TTF/include/SDL_ttf.h"
#pragma comment( lib, "TTF/lib/SDL2_ttf.lib" )

Font::~Font()
{
	delete buffer;
	TTF_CloseFont(font);
}

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
	for (size_t i = 0; i < fonts.size(); ++i)
		if (fonts[i].use_count() <= 1)
			fonts.erase(fonts.begin() + i);

	return true;
}

bool Fonts::CleanUp()
{
	fonts.clear();
	return true;
}

FontPtr Fonts::Load(const std::string& path, int size)
{
	char* buffer = nullptr;
	TTF_Font* font = TTF_OpenFontRW(game->assets->Load(path.c_str(), &buffer), 1, size);

	if (!font)
	{
		game->Log("Loading font -> Bad Thing, Error in " + path + " -> " + SDL_GetError());
		return nullptr;
	}

	FontPtr output = std::make_shared<Font>(buffer, font);
	fonts.push_back(output);

	return output;
}

Surface* Fonts::TextToSurface(FontData* font, const std::string& text, Color color)
{
	return TTF_RenderText_Solid(font, text.c_str(), color.ToSDL());
}