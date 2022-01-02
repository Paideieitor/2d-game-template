#include "Timer.h"

#include "SDL/include/SDL_timer.h"

Timer::Timer(int offset) : start(SDL_GetTicks() - offset), pausedAt(0)
{
}

Timer::~Timer()
{

}

void Timer::Start()
{
	start = SDL_GetTicks();
}

void Timer::Stop()
{
	start = -1;
	pausedAt = 0;
}

int Timer::Read()
{
	if (start < 0)
		return 0;
	if(pausedAt != 0)
		return pausedAt;
	return SDL_GetTicks() - start;
}

float Timer::ReadSec()
{
	if (start < 0)
		return 0.0f;
	if(pausedAt != 0)
		return pausedAt / 1000.0f;
	return (SDL_GetTicks() - start) / 1000.0f;
}

void Timer::Pause()
{
	if (start < 0)
		return;
	if(pausedAt == 0)
		pausedAt = Read();
}

void Timer::Play()
{
	if(pausedAt != 0)
	{
		start = SDL_GetTicks() - pausedAt;
		pausedAt = 0;
	}
}
