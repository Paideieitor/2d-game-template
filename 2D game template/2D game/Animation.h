#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"
#include "Timer.h"

#include <vector>
#include <memory>

class AnimationData;
typedef std::shared_ptr<AnimationData> Animation;

Animation MakeAnimation(bool loop, float speed);
Animation MakeAnimation(bool loop, float speed, const ipoint& position, const ipoint& size);
Animation MakeAnimation(bool loop, float speed, unsigned int amount, const ipoint& initialpos, const ipoint& size, unsigned int columns, 
	unsigned int rows);

class AnimationData
{
public:
	
	AnimationData() = delete;
	AnimationData(bool loop, float speed) : loop(loop), speed(speed), current(0) { timer.Start(); }

	void AddFrame(const ipoint& position, const ipoint& size) { frames.emplace_back(Frame(position, size)); }
	void AddFrames(unsigned int amount, const ipoint& initialpos, const ipoint& size, unsigned int columns, unsigned int rows)
	{
		unsigned int column = 0;
		unsigned int row = 0;
		for (unsigned int i = 0; i < amount; ++i)
		{
			ipoint position = initialpos;
			position.x += size.x * column;
			position.y += size.y * row;

			AddFrame(position, size);

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

	const Frame GetFrame()
	{
		if (timer.CheckSec(speed))
		{
			++current;
			if (current >= frames.size())
				current = 0;
		}

		return frames[current];
	}
	const ipoint GetCurrentSize() { return frames[current].size; }

	void Pause() { timer.Pause(); }
	void Resume() { timer.Play(); }
	void Reset() { current = 0; timer.Start(); }

public:

	bool loop;
	float speed;

private:

	size_t current;
	std::vector<Frame> frames;

	Timer timer;

	friend Animation MakeAnimation(bool loop, float speed);
	friend Animation MakeAnimation(bool loop, float speed, const ipoint& position, const ipoint& size);
	friend Animation MakeAnimation(bool loop, float speed, unsigned int amount, const ipoint& initialpos, const ipoint& size, unsigned int columns, 
		unsigned int rows);
};

#endif
