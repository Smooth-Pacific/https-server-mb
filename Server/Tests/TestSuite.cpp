#include "TestSuite.hpp"

#include "TestServerOptions.hpp" 

#include <iostream>
#include <cstdlib>

#define TEST(X) std::cout << "Testing: " << #X << std::endl;\
                X();\
                std::cout << "Test passed.\n\n"

int main() {

    std::cout << "Test Suite\n";
    
    // Test ServerOptions struct
    if (std::getenv("SET") == NULL) {
        TEST(test_server_options_empty_environment);
    } else {
        TEST(test_server_options_set_environment);
    }

    // Test root endpoints requests
    //TEST(test_root_endpoint_GET);
    //TEST(test_root_endpoint_PUT);
    //TEST(test_root_endpoint_POST);
    //TEST(test_root_endpoint_DELETE);

    return 0;
}
