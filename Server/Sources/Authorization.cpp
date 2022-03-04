#include "Authorization.hpp"

#include <iostream>
#include <random>

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

std::string Authorization::GenerateOpaque(size_t size) {

    const char* const hex = "ABCDEF0123456789";
    thread_local static std::mt19937 rng{std::random_device{}()};
    thread_local static std::uniform_int_distribution<int> select(0, 15);

    std::string random_opaque(size, '0');
    for (auto& i : random_opaque) {
        i = hex[select(rng)];
    }

    return random_opaque;
}
