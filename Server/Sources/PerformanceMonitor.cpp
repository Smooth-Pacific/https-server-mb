#include "PerformanceMonitor.hpp"

#include <iostream>
//#include <fstream> // TODO
#include <chrono>
#include <thread>

void PerformanceMonitor::operator () (void) {
    while (true) {
        std::cout << "Doing Performance Monitoring" << std::endl;

        auto time_ms = 1'000u;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
    }
}
