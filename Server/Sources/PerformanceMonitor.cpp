#include "PerformanceMonitor.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

#include <sys/sysinfo.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

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

    // Init time
    auto time_now = std::chrono::system_clock::now();
    auto ct = std::chrono::system_clock::to_time_t(time_now);
    fs << std::ctime(&ct);
    fs.flush();
    
    while (true) {
        // System monitoring
        fs << "Doing Performance Monitoring\n";
        fs.flush();

        auto time_ms = 3'000u;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
    }

}
