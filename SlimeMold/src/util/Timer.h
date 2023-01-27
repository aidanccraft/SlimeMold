#pragma once

#include "Global.h"
#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime, stopwatchStart;
public:
    Timer();
    void setStopwatch();
    long long getStopwatch();
    long long getDelta();
};