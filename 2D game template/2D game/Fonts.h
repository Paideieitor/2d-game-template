#ifndef FONTS_H
#define FONTS_H

#include "Module.h"

#include "TTF/include/SDL_ttf.h"
#pragma comment( lib, "TTF/lib/SDL2_ttf.lib" )

struct Font
{
	Font(char* buffer, TTF_Font* font)
	{
		this->buffer = buffer;
		this->font = font;
	}

	~Font()
	{
		delete buffer;
		TTF_CloseFont(font);
	}

	char* buffer;
	TTF_Font* font;
};

class Fonts : public Module
{
public:

	Fonts();
	~Fonts();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	TTF_Font* Load(const char* path, int size);

	SDL_Texture* GetTextTexture(TTF_Font* font, const char* text, color color);

private:

	vector<Font*> fonts;
};

#endif