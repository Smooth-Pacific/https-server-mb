#include "Logger.hpp"
#include <iostream>

[[nodiscard]]
bool Logger::log_success(std::string message) {

    std::cout << success_prefix << " " << message << std::endl;

    return true;
}

[[nodiscard]]
bool Logger::log_failure(std::string message) {

    std::cout << failure_prefix << " " << message << std::endl;

    return true;
}

void Logger::custom_log_access(const std::string& url) {
    // TODO: Log in logs.txt?
    std::cout << "Accessing: " << url << std::endl;
}
