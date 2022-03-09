#ifndef PERFORMANCE_MONITOR_HEADER
#define PERFORMANCE_MONITOR_HEADER

#include "ServerOptions.hpp"

class PerformanceMonitor {
private:
    const char* const file_path = "logs";
    const char* const file_name = "performance.log";
public:
    void operator () (const ServerOptions&);
};

#endif // PERFORMANCE_MONITOR_HEADER
