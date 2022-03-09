#include "Logger.hpp"

#ifndef NDEBUG
#include <iostream>
#endif // NDEBUG

#ifndef DT_FORMAT
#define DT_FORMAT       "%Y-%m-%d %H:%M:%S %Z"
#endif // DT_FORMAT

#ifndef DT_FORMAT_SIZE
#define DT_FORMAT_SIZE  30
#endif // DT_FORMAT_SIZE

[[nodiscard]]
static inline std::string GetCurrentTime() {

    using std::string;

    string      current_time{"[Date] "};
    char        buffer[DT_FORMAT_SIZE]{0};
    time_t      time;
    tm*         ptm;

    std::time(&time);
    ptm = localtime(&time);

    strftime(buffer, sizeof(buffer), DT_FORMAT, ptm);
    current_time += string(buffer);

    return current_time;

}

[[nodiscard]]
bool Logger::log_success(const httpserver::http_request& req) {

#ifndef NDEBUG
    std::cout << GetCurrentTime() << "\n"
              << "[Success] " << req << std::endl;
#endif // NDEBUG
    ofs << GetCurrentTime() << "\n"
        << "[Success] " << req << std::endl;

    return true;
}

[[nodiscard]]
bool Logger::log_failure(const httpserver::http_request& req) {

#ifndef NDEBUG
    std::cerr << GetCurrentTime() << "\n"
              << "[Failure] " << req << std::endl;
#endif // NDEBUG
    ofs << GetCurrentTime() << "\n"
        << "[Failure] " << req << std::endl;

    return true;
}

void Logger::custom_log_access(const httpserver::http_request& req) {
#ifndef NDEBUG
    std::cout << GetCurrentTime() << "\n"
              << "[Event] " << req << std::endl;
#endif // NDEBUG
    ofs << GetCurrentTime() << "\n"
        <<"[Event] " << req << std::endl;
}
