#ifndef TEXTURES_H
#define TEXTURES_H

#include "Module.h"
#include "Fonts.h"

struct Texture
{
	Texture() {}
	Texture(string path, SDL_Texture* texture)
	{
		this->path = path;
		this->texture = texture;
	}

	~Texture()
	{
		SDL_DestroyTexture(texture);
	}

	string path;

	SDL_Texture* texture;
};

class Textures : public Module
{
public:

	Textures();
	~Textures();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	SDL_Texture* Load(const char* path);
	SDL_Texture* LoadText(TTF_Font* font, const char* text, color color, ipoint& size);
	void Unload(SDL_Texture*);

	SDL_Texture* SurfaceToTexture(SDL_Surface*);

	ipoint GetTextureSize(SDL_Texture*);

private:

	vector<Texture*> textures; 
};

#endif
