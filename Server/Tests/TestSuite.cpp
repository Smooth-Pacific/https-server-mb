#include "TestSuite.hpp" // TEST

#include "TestServerOptions.hpp" 
//#include "TestPerformanceMonitor.hpp" 
//#include "TestHelloResource.hpp" 
//#include "TestRootResource.hpp" 

#include <iostream>
#include <cstdlib>

int main() {

    unsigned passed = 0;
    unsigned failed = 0;

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

    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n" << std::endl;

    return 0;
}
