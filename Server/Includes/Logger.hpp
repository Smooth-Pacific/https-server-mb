#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#include <fstream>
#include <string>

class Logger {
private: // Member variables
    std::string file_name = "log.txt";
    std::string log_directory = "logs";
    std::string success_prefix = "Success: ";
    std::string failure_prefix = "Failure: ";
public: // Constructors
    Logger() = delete;
    ~Logger() = delete;
public: // Non-static member functions
    bool log_success(std::string);
    bool log_failure(std::string);
public: // Static member functions
    static void custom_log_access(const std::string&);
};

#endif // LOGGER_HEADER
