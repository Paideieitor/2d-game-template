#ifndef COLOR_H
#define COLOR_H

#include "SDL/include/SDL.h"

struct color
{
	color(unsigned int r = 0u, unsigned int g = 0u, unsigned int b = 0u, unsigned int a = 255u)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	SDL_Color ToSDL()
	{
		SDL_Color output = { r, g, b, a };

		return output;
	}

	void Set(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255u)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	void SetAlpha(unsigned int a)
	{
		this->a = a;
	}

	void Red(unsigned int a = -1)
	{
		r = 255u;
		g = 0u;
		b = 0u;

		if (a >= 0)
			this->a = a;
	}
	void Green(unsigned int a = -1)
	{
		r = 0u;
		g = 255u;
		b = 0u;

		if (a >= 0)
			this->a = a;
	}
	void Blue(unsigned int a = -1)
	{
		r = 0u;
		g = 0u;
		b = 255u;

		if (a >= 0)
			this->a = a;
	}
	void White(unsigned int a = -1)
	{
		r = 255u;
		g = 255u;
		b = 255u;

		if (a >= 0)
			this->a = a;
	}
	void Black(unsigned int a = -1)
	{
		r = 0u;
		g = 0u;
		b = 0u;

		if (a >= 0)
			this->a = a;
	}

	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;

	color operator+(int n)
	{
		int red = r;
		int green = g;
		int blue = b;

		red += n;
		if (red > 255)
			red = 255;
		green += n;
		if (green > 255)
			green = 255;
		blue += n;
		if (blue > 255)
			blue = 255;

		color output(red, green, blue, a);
		return output;
	}
	color operator-(int n)
	{
		int red = r;
		int green = g;
		int blue = b;

		red -= n;
		if (red < 0)
			red = 0;
		green -= n;
		if (green < 0)
			green = 0;
		blue -= n;
		if (blue < 0)
			blue = 0;

		color output(red, green, blue, a);
		return output;
	}

};

#endif