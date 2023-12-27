#pragma once

#include <chrono>

class Stopwatch
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

public:
	Stopwatch();

	float lap();
	float elapsed() const;
};