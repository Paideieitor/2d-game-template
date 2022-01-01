#include "Color.h"

#include "SDL/include/SDL_pixels.h"

const Color Color::red = Color(255u, 0u, 0u);
const Color Color::green = Color(0u, 255u, 0u);
const Color Color::blue = Color(0u, 0u, 255u);

const Color Color::black = Color(0u, 0u, 0u);
const Color Color::white = Color(255u, 255u, 255u);

const Color Color::null = Color();

SDL_Color Color::ToSDL() const
{
	SDL_Color output = { (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };

	return output;
}
