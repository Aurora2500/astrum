#include "stopwatch.hpp"

Stopwatch::Stopwatch()
{
	m_start = std::chrono::high_resolution_clock::now();
}

float Stopwatch::lap()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto diff = now - m_start;
	m_start = now;
	return std::chrono::duration<double, std::milli>(diff).count();
}

float Stopwatch::elapsed() const
{
	auto now = std::chrono::high_resolution_clock::now();
	auto diff = now - m_start;
	return std::chrono::duration<double, std::milli>(diff).count();
}