#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#include <httpserver.hpp>
#include <fstream>
#include <string>

class Logger {
private: // Member variables
    std::string log_directory;
    std::string log_file;
    std::ofstream ofs;
public: // Constructors
    Logger()
        : log_directory("logs/")
        , log_file("server.log")
        , ofs(log_directory + log_file, std::ios::app | std::ios::out)
    {
    }
    ~Logger()
    {
        ofs.close();
    }
public: // Non-static member functions
    bool log_success(const httpserver::http_request& req);
    bool log_failure(const httpserver::http_request& req);
public: // Static member functions
    void custom_log_access(const httpserver::http_request& req);
};

#endif // LOGGER_HEADER
