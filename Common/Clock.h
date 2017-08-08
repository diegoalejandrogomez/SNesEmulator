#pragma once
#include <chrono>
#include <functional>

class Clock
{
private:
	double frequency;
	std::chrono::high_resolution_clock clock;
	std::function<void()> function;
	std::chrono::time_point<std::chrono::steady_clock> lastCheck;
	std::chrono::milliseconds elapsed;

public:
	Clock(double frequency, double unit);
	~Clock();

	void SetOnTick(std::function<void()> function);
	void Update();
};

