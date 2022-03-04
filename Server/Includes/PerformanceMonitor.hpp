#ifndef PERFORMANCE_MONITOR_HEADER
#define PERFORMANCE_MONITOR_HEADER

class PerformanceMonitor {
private:
    const char* const file_path = "logs";
    const char* const file_name = "performance.log";
public:
    void operator () (void);
};

#endif // PERFORMANCE_MONITOR_HEADER
