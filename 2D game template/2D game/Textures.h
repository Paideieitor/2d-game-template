#ifndef TEXTURES_H
#define TEXTURES_H

#include "Module.h"
#include "Fonts.h"

typedef struct SDL_Texture TextureData;

class Texture
{
public:
	Texture() = delete;
	Texture(const Texture& newTexture) = delete;

	~Texture();

	const ipoint GetSize() const { return size; }

private:

	Texture(const string& path, TextureData* texture);

	string path;
	TextureData* texture;
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
	void Unload(Texture*&);

	void ChangeTexture(Texture*& source, Texture*& destination);

private:

	TextureData* SurfaceToTexture(Surface*);

	vector<Texture*> textures; 
};

#endif
