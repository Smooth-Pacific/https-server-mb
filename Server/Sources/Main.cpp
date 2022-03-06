/**
 * Creator:    VPR
 * Created:    January 27th, 2022
 * Updated:    March 5th, 2022
 *
 * Description:
 *     - [x] Implement Digest Authentication for calls to server
 *     - [x] Implement Thread Pooling for CPUs with > 4 cores
 *     - [x] Implement Multi-threading per connection
 *     - [x] Implement Dedicated thread to perform Live Performance Monitoring
 *     - [x] Implement Custom Options
 *     - [x] Implement TLS/HTTPS
**/

#include "PerformanceMonitor.hpp" // PerformanceMonitor
#include "ServerOptions.hpp"      // ServerOptions struct
#include "Authorization.hpp"      // Authorization
#include "Resources.hpp"          // Resource endpoints

#include <httpserver.hpp>         // libhttpserver
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <future>

int main() {

    // Create utopia-server using server options variables
    ServerOptions so;
    create_webserver cw = create_webserver(so.Port())
        .use_ssl()
        .regex_checking()
        .deferred()
        .ban_system()
#ifndef NDEBUG
        .debug()
#else
        .pedantic()
#endif // NDEBUG
        .per_IP_connection_limit(so.PerIpConnectionLimit())
        .connection_timeout(so.Timeout())
        .content_size_limit(so.ContentSizeLimit())
        .max_connections(so.MaxConnections())
        .max_threads(so.MaxThreads())
        .max_thread_stack_size(so.MaxThreadStackSize())
        .memory_limit(so.MemoryLimit());

    // Use IPV6
    if (so.InternetProtocol() == IPV6_PROTOCOL) {
        cw.use_ipv6();
    }

    // Set server crt
    if (std::filesystem::is_regular_file(so.MemCert())) {
        cw.https_mem_cert(so.MemCert());
    } else {
        std::cerr << "ERROR: to find certificate authority crt." << std::endl;
        exit(126);
    }

    // Set server key
    if (std::filesystem::is_regular_file(so.MemKey())) {
        cw.https_mem_key(so.MemKey());
    } else {
        std::cerr << "ERROR: Failed to find certificate authority key." << std::endl;
        exit(127);
    }

    // Enable dual stack
    if (so.DualStackEnabled()) {
        cw.use_dual_stack();
    }

    // Create web server and set resource endpoints
    webserver ws = cw;

    root_resource   root_res;
    hello_resource  hw_res;
    mime_resource   mime_res;

    ws.register_resource("/", &root_res);
    ws.register_resource("/hello", &hw_res);
    ws.register_resource("/mime/{arg1}", &mime_res);
#ifndef NDEBUG
    std::cout << "Starting server with options:\n" << so << std::endl;
#else
    // Log startup time with options
#endif

    // Begin performance monitoring thread
    auto performance_thread = std::async(std::launch::async, PerformanceMonitor());

    // Start web server
    ws.start(true);

    return 0;
}
