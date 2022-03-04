#include "Authorization.hpp"

#include <iostream>

std::string Authorization::LoadUsername() {
    return (std::getenv("AUTH_USER") ? std::getenv("AUTH_USER") : "");
}

std::string Authorization::LoadPassword() {
    return (std::getenv("AUTH_PASS") ? std::getenv("AUTH_PASS") : "");
}

void Authorization::ValidateUsername() {
    if (username == "") {
        std::cerr << "Failed to initialize credentials";
        exit(2);
    }
}

void Authorization::ValidatePassword() {
    if (password == "") {
        std::cerr << "Failed to initialize credentials.\n";
        // reason
        exit(2);
    } else if (password.length() < 8) {
        std::cerr << "Failed to initialize credentials.\n";
        // reason
        exit(2);
    }
}
