#pragma once
#include <chrono>
#include <iostream>

class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;

public:
    Timer();
    ~Timer();
};
