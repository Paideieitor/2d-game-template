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

	ipoint GetSize() { return size; }

private:

	Texture(string path, SDL_Texture* texture) : path(path), texture(texture), instances(0), font(nullptr), color()
	{
		SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	}

	string path;
	SDL_Texture* texture;
	ipoint size;

	int instances;

	Font* font;
	Color color;

	friend class Textures;
	friend class Render;
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
	Texture* LoadText(Font* font, const char* text, Color color);
	void Unload(Texture*);

	void ChangeTexture(Texture*& source, Texture*& destination);

private:

	SDL_Texture* SurfaceToTexture(SDL_Surface*);

	vector<Texture*> textures; 
};

#endif
