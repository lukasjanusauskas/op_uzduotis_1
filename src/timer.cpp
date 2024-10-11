#include <chrono>
#include <iostream>
#include <string>

class Timer{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed;

public:
    void start_timer(){ this->start = std::chrono::high_resolution_clock::now();}
    double get_time(){
        this->end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        return elapsed.count();
    }

    void restart_timer(){ this->start = std::chrono::high_resolution_clock::now();}
};