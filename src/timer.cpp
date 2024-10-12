#include <chrono>
#include <iostream>
#include <string>

#include "timer.h"

void Timer::start_timer(){ 
    this->start = std::chrono::high_resolution_clock::now();
}

double Timer::get_time(){
    this->end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    return elapsed.count();
}

void Timer::restart_timer(){ 
    this->start = std::chrono::high_resolution_clock::now();
}