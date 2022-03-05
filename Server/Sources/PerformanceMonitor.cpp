#include "PerformanceMonitor.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>

//#include <sys/sysinfo.h>
//#include <sys/times.h>
//#include <sys/types.h>
//#include <unistd.h>

#define DT_FORMAT       "[%Y-%m-%d %H:%M:%S %Z]"
#define DT_FORMAT_SIZE  32

static inline std::string GetCurrentTime() {

    using std::string;

    string      time_fmt;
    char        buffer[DT_FORMAT_SIZE]{0};
    time_t      time;
    tm*         ptm;

    std::time(&time);
    ptm = localtime(&time);

    strftime(buffer, sizeof(buffer), DT_FORMAT, ptm);
    time_fmt = buffer;

    return time_fmt;

}

//static inline std::string GetSystemName() {
    //return 0;
//}

void PerformanceMonitor::operator () (void) {

    const std::string full_path = [this]() -> const std::string {
        std::string _full_path;
        _full_path.reserve(256);
        _full_path += file_path;
        _full_path += "/";
        _full_path += file_name;
        return _full_path;
    }();

    // Create log directory it doesn't exist
    if (!std::filesystem::is_directory(file_path)) {
        std::filesystem::create_directory(file_path);
    }

    // Create log file if it doesn't exist
    std::fstream fs;
    fs.open(full_path, std::fstream::app | std::fstream::out | std::fstream::in);

    if (!fs.is_open()) {
        std::cerr << "Failed to open '" << full_path << "'" << std::endl;
        exit(3);
    }

    // Log time of initiation
    fs << GetCurrentTime() << "\n";
    fs.flush();
    
    while (true) {
        // System monitoring
        fs << "Doing Performance Monitoring\n";
        fs.flush();

        auto time_ms = 12'500u;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
    }

}
