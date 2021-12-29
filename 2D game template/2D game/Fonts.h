#ifndef FONTS_H
#define FONTS_H

#include "Module.h"

typedef struct _TTF_Font FontData;
typedef struct SDL_Surface Surface;

class Font
{
public:
	Font(char* buffer, FontData* font) : buffer(buffer), font(font) {}

	~Font();

private:
	char* buffer;
	FontData* font;

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
	void Unload(Font*&);

private:

	Surface* TextToSurface(FontData* font, const char* text, Color color);
	vector<Font*> fonts;

	friend class Textures;
};

#endif