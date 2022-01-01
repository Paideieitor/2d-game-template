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
	Texture(const std::string& path, TextureData* texture);

	~Texture();

	const ipoint GetSize() const { return size; }

private:

	std::string path;
	TextureData* texture;
	ipoint size;

	FontPtr font;
	Color color;

	friend class Textures;
	friend class Render;
};

typedef std::shared_ptr<Texture> TexturePtr;

class Textures : public Module
{
public:

	Textures();
	~Textures();

	bool SetUp(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	TexturePtr Load(const std::string& path);
	TexturePtr LoadText(FontPtr font, const std::string& text, Color color);

private:

	TextureData* SurfaceToTexture(Surface*);

	std::vector<TexturePtr> textures;
};

#endif
