#ifndef PERFORMANCE_MONITOR_HEADER
#define PERFORMANCE_MONITOR_HEADER

#include <iostream>
//#include <fstream>
#include <chrono>
#include <thread>

class PerformanceMonitor {
public:
    void operator () (void) {
        while (true) {
            std::cout << "Doing Performance Monitoring" << std::endl;

            auto time_ms = 1'000u;
            std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
        }
    }
};

#endif // PERFORMANCE_MONITOR_HEADER
