#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"
#include "Timer.h"

#include <vector>

class Animation
{
public:
	
	Animation() = delete;
	Animation(bool loop, float speed) : loop(loop), speed(speed) {}
	Animation(bool loop, float speed, ipoint position, ipoint size) : loop(loop), speed(speed) { AddFrame(position, size); }
	Animation(bool loop, float speed, unsigned int amount, ipoint initialpos, ipoint size, unsigned int columns, unsigned int rows)
		: loop(loop), speed(speed) { AddFrames(amount, initialpos, size, columns, rows); }

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



public:

	bool loop;
	float speed;

private:

	Timer timer;

	std::vector<Frame> frames;

};

#endif
