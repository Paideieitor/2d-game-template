#include "PerfTimer.h"
#include "SDL\include\SDL_timer.h"

unsigned int PerfTimer::frequency = 0;


PerfTimer::PerfTimer()
{
	if (frequency == 0)
		frequency = SDL_GetPerformanceFrequency();

	Start();
}


void PerfTimer::Start()
{
	started_at = SDL_GetPerformanceCounter();
}


long double PerfTimer::ReadMs() const
{
	return 1000.0 * (long double(SDL_GetPerformanceCounter() - started_at) / long double(frequency));
}


unsigned int PerfTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() - started_at;
}
