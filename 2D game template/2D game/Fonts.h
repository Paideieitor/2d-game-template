#ifndef FONTS_H
#define FONTS_H

#include "Module.h"

#include "TTF/include/SDL_ttf.h"
#pragma comment( lib, "TTF/lib/SDL2_ttf.lib" )

class Font
{
public:
	Font(char* buffer, TTF_Font* font) : buffer(buffer), font(font) {}

	~Font()
	{
		delete buffer;
		TTF_CloseFont(font);
	}

private:
	char* buffer;
	TTF_Font* font;

	friend class Fonts;
	friend class Textures;
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

	Font* Load(const char* path, int size);

private:

	SDL_Surface* TextToSurface(TTF_Font* font, const char* text, Color color);
	vector<Font*> fonts;

	friend class Textures;
};

#endif