#ifndef TEXTURES_H
#define TEXTURES_H

#include "Module.h"
#include "Fonts.h"

class Texture
{
public:
	Texture() = delete;
	Texture(string path, SDL_Texture* texture) : path(path), texture(texture) {}

	~Texture()
	{
		SDL_DestroyTexture(texture);
	}

	SDL_Texture* const Get() const { return texture; }

private:
	string path;

	SDL_Texture* texture;

	friend class Textures;
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

	Texture* Load(const char* path);
	Texture* LoadText(Font* font, const char* text, color color, ipoint& size);
	void Unload(Texture*);

	ipoint GetTextureSize(Texture*);

private:

	SDL_Texture* SurfaceToTexture(SDL_Surface*);

	vector<Texture*> textures; 
};

#endif
