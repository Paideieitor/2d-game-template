#ifndef TEXTURES_H
#define TEXTURES_H

#include "Module.h"
#include "Fonts.h"

class Texture
{
public:
	Texture() = delete;
	Texture(const Texture& newTexture) = delete;

	~Texture()
	{
		SDL_DestroyTexture(texture);
	}

	SDL_Texture* const Get() const { return texture; }

private:

	Texture(string path, SDL_Texture* texture) : path(path), texture(texture), instances(0), font(nullptr), color() {}

	string path;

	SDL_Texture* texture;

	int instances;

	Font* font;
	Color color;

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
	Texture* LoadText(Font* font, const char* text, Color color, ipoint& size);
	void Unload(Texture*);

	ipoint GetTextureSize(Texture*);

	void ChangeTexture(Texture*& source, Texture*& destination);

private:

	SDL_Texture* SurfaceToTexture(SDL_Surface*);

	vector<Texture*> textures; 
};

#endif
