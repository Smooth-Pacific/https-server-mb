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


#ifndef DT_FORMAT
#define DT_FORMAT       "%Y-%m-%d %H:%M:%S %Z"
#endif // DT_FORMAT

#ifndef DT_FORMAT_SIZE
#define DT_FORMAT_SIZE  30
#endif // DT_FORMAT_SIZE

#ifndef LOG_ERR_EXIT
#define LOG_ERR_EXIT    5
#endif // LOG_ERR_EXIT

[[nodiscard]]
static inline std::string GetCurrentTime() {

    using std::string;

    string      current_time{"[Date]\n"};
    char        buffer[DT_FORMAT_SIZE]{0};
    time_t      time;
    tm*         ptm;

    std::time(&time);
    ptm = localtime(&time);

    strftime(buffer, sizeof(buffer), DT_FORMAT, ptm);
    current_time += string(buffer) + "\n";

    return current_time;

}

[[nodiscard]]
static inline std::string GetSystemHardware() {

    using std::string;

    string system_hardware{"[System Hardware]\n"};
    system_hardware.reserve(1024 * 4);

    std::ifstream ifs("/proc/cpuinfo");
    if (ifs.is_open()) {
        string buffer(256, 0);
        for (size_t i = 0; ifs.good(); i++) {
            std::getline(ifs, buffer);

            if (buffer.starts_with("\n")) {
                continue;
            } else if ( buffer.starts_with("model name")
                        || buffer.starts_with("cpu M")
                        || buffer.starts_with("cache")
                        || buffer.starts_with("vendor")
                        || buffer.starts_with("address")
                        || buffer.starts_with("core id") )
            {
                system_hardware += buffer + "\n";
            } else if (buffer.starts_with("power")) {
                system_hardware += "\n";
            }
        }
        system_hardware = system_hardware.substr(0, system_hardware.length()-1);
    } else {
        std::cerr << "Failed to open '/proc/cpuinfo'\n" << std::flush;
        exit(LOG_ERR_EXIT);
    }

    return system_hardware;
    
}

[[nodiscard]]
static inline std::string GetSystemMemory() {

    using std::string;

    string system_memory{"[System Memory]\n"};
    system_memory.reserve(1024);

    std::ifstream ifs("/proc/meminfo");
    if (ifs.is_open()) {
        string buffer(256, 0);
        for (size_t i = 0; ifs.good(); i++) {
            std::getline(ifs, buffer);

            if (buffer.starts_with("\n")) {
                continue;
            }
            if ( buffer.starts_with("Mem") || buffer.starts_with("Active") || buffer.starts_with("Swap") ) {
                system_memory += buffer + "\n";
            }
        }
    } else {
        std::cerr << "Failed to open '/proc/meminfo'\n" << std::flush;
        exit(LOG_ERR_EXIT);
    }

    return system_memory;
}

[[nodiscard]]
static inline std::string GetProcessInformation() {

    using std::string;

    string process_info{"[Process Information]\n"};
    process_info.reserve(1024);

    std::ifstream ifs("/proc/self/status");
    if (ifs.is_open()) {
        string buffer(256, 0);
        for (size_t i = 0; ifs.good(); i++) {
            std::getline(ifs, buffer);

            if (buffer.starts_with("\n")) {
                continue;
            }
            if ( buffer.starts_with("Name")
                 || buffer.starts_with("Pid")
                 || buffer.starts_with("PPid")
                 || buffer.starts_with("Vm")
                 || buffer.starts_with("Gid")
                 || buffer.starts_with("Uid")
                 || buffer.starts_with("Thread") )
            {
                process_info += buffer + "\n";
            }
        }
    } else {
        std::cerr << "Failed to open '/proc/self/status'\n" << std::flush;
        exit(LOG_ERR_EXIT);
    }

    return process_info;

}

[[nodiscard]]
static inline std::string GetSystemResources() {

    using std::string;


    
    return 0;
}

void PerformanceMonitor::operator () (const ServerOptions& so) {

    const auto full_path = [this]() -> const std::string {
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
        exit(LOG_ERR_EXIT);
    }

    // Log server options on startup
    fs << GetCurrentTime() << "\n";
    fs << "[Starting Server]\n";
    fs << so << "\n";
    fs.flush();

    while (true) {

        /**
         * Live system performance logging
        **/
        fs << GetCurrentTime()        << "\n"
           << GetSystemHardware()     << "\n"
           << GetSystemMemory()       << "\n"
           << GetProcessInformation() << "\n"
           << GetSystemResources()    << "\n";
        fs.flush();

        auto time_ms = 12'500u;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));

    }

}
