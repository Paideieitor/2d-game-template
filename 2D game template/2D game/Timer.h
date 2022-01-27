#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:

	Timer(int offset = 0);
	~Timer();

	void Start();
	void Stop();

	int Read();
	float ReadSec();

	void Pause();
	void Play();
	void Delay(int delay);

	bool Check(int time, bool restart = true);
	bool CheckSec(float time, bool restart = true);

private:

	int start;
	int pausedAt;
};

#endif