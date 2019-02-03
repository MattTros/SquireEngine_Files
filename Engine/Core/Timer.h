#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

struct WaitForSeconds
{
	inline WaitForSeconds()
	{
		active = false;
		seconds = 0.0f;
		waitTime = 0.0f;
	}
	inline WaitForSeconds(bool active_, float waitTime_)
	{
		active = active_;
		seconds = 0.0f;
		waitTime = waitTime_;
	}
	inline void Reset()
	{
		active = false;
		seconds = 0.0f;
		waitTime = 0.0f;
	}
	bool active;
	float seconds;
	float waitTime;
};

class Timer
{
public:
	Timer();
	~Timer();

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator = (const Timer&) = delete;
	Timer& operator = (Timer&&) = delete;

	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTicks() const;
private:
	unsigned int prevTicks;
	unsigned int currentTicks;
};

#endif // !TIMER_H

