#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__

class PerfTimer
{
public:

	PerfTimer();

	void Start();
	long double ReadMs() const;
	unsigned int ReadTicks() const;

private:
	unsigned int	started_at;
	static unsigned int frequency;
};

#endif //__PERFTIMER_H__