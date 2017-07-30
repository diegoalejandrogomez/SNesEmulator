#include "stdafx.h"
#include "Clock.h"
#include "FrequencyUnits.h"

Clock::Clock(double frequency, double unit)
{
	this->frequency = frequency * unit;
	lastCheck = clock.now();
	elapsed.zero();
}


Clock::~Clock()
{
}

void Clock::SetOnTick(std::function<void()> function)
{
	this->function = function;
}

void Clock::Update()
{
	std::chrono::time_point<std::chrono::steady_clock> now = clock.now();
	elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCheck);
	lastCheck = now;
	if (elapsed.count() >=  (1 / frequency))
	{
		this->function();
		elapsed.zero();
	}

}
