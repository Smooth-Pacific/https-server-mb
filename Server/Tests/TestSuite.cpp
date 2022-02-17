#include <iostream>
#include "TestSuite.hpp"
#include "TestServerOptions.hpp"

#define TEST(X) std::cout << "Testing: " << #X << std::endl;\
                X();\
                std::cout << "Test passed.\n\n"

int main() {

    std::cout << "Test Suite\n";
    
    // Test ServerOptions struct
    TEST(test_server_options_empty_environment);
    //TEST(test_server_options_set_environment);

    return 0;
}
