#include "timer.h"

Timer::Timer()
{
    start = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
    end = std::chrono::steady_clock::now();

    std::cout << "Elapsed time : "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " sec"
              << std::endl;
}
