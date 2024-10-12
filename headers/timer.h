#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed;

public:
    void start_timer();
    double get_time();
    void restart_timer();
};

#endif