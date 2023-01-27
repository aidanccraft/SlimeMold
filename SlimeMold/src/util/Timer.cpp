#include "Timer.h"

Timer::Timer() {
	lastTime = std::chrono::high_resolution_clock::now();
	stopwatchStart = lastTime;
}

void Timer::setStopwatch() {
	stopwatchStart = std::chrono::high_resolution_clock::now();
}

long long Timer::getStopwatch() {
	std::chrono::time_point<std::chrono::high_resolution_clock> stopwatchEnd = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(stopwatchStart).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(stopwatchEnd).time_since_epoch().count();

	return end - start;
}

long long Timer::getDelta() {
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(lastTime).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(currentTime).time_since_epoch().count();

	lastTime = currentTime;
	return end - start;
}