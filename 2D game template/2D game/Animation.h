#ifndef ANIMATION_H
#define ANIMATION_H

#include "Point.h"

#include <vector>

class Animation
{
private:

	struct Frame
	{
		Frame() = delete;
		Frame(const ipoint& position, const ipoint& size) : position(position), size(size) {}

		const ipoint position;
		const ipoint size;
	};

	std::vector<Frame> frames;

public:

	void AddFrame(ipoint position, ipoint size) { frames.emplace_back(Frame(position, size)); }
	void AddFrames(unsigned int amount, ipoint initialpos, ipoint size, unsigned int columns, unsigned int rows)
	{
		unsigned int column = 0;
		unsigned int row = 0;
		for (unsigned int i = 0; i < amount; ++i)
		{
			ipoint position = initialpos;
			position.x += size.x * column;
			position.y += size.y * row;

			AddFrame(initialpos, size);

			++column;
			if (column >= columns)
			{
				column = 0;

				++row;
				if (row >= rows)
					return;
			}
		}
	}
};

#endif
