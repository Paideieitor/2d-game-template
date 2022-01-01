#ifndef COLOR_H
#define COLOR_H

struct SDL_Color;

struct Color
{
	Color() : r(-1), g(-1), b(-1), a(-1) {}
	Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255u) : r(r), g(g), b(b), a(a) {}

	SDL_Color ToSDL() const;

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

	void SetRed(int a = -1)
	{
		r = 255u;
		g = 0u;
		b = 0u;

		if (a >= 0 && a <= 255)
			this->a = (unsigned int)a;
	}
	void SetGreen(int a = -1)
	{
		r = 0u;
		g = 255u;
		b = 0u;

		if (a >= 0 && a <= 255)
			this->a = (unsigned int)a;
	}
	void SetBlue(int a = -1)
	{
		r = 0u;
		g = 0u;
		b = 255u;

		if (a >= 0 && a <= 255)
			this->a = (unsigned int)a;
	}
	void SetBlack(int a = -1)
	{
		r = 0u;
		g = 0u;
		b = 0u;

		if (a >= 0 && a <= 255)
			this->a = (unsigned int)a;
	}
	void SetWhite(int a = -1)
	{
		r = 255u;
		g = 255u;
		b = 255u;

		if (a >= 0 && a <= 255)
			this->a = (unsigned int)a;
	}

	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;

	Color operator+(int n) const
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

		Color output(red, green, blue, a);
		return output;
	}
	Color operator-(int n) const
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

		Color output(red, green, blue, a);
		return output;
	}

	bool operator==(const Color& color) const
	{
		if (color.r == r && color.b == b && color.g == g && color.a == a)
			return true;
		return false;
	}
	bool operator!=(const Color& color) const
	{
		if (color.r != r && color.b != b && color.g != g || color.a != a)
			return true;
		return false;
	}

	static const Color red;
	static const Color green;
	static const Color blue;

	static const Color black;
	static const Color white;

	static const Color null;
};

#endif
