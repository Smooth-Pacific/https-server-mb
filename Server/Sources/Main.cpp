/**
 * Creator:    VPR
 * Created:    January 27th, 2022
 * Updated:    February 16th, 2022
 *
 * Description:
 *     - [-] Implement Thread Pooling for CPUs with > 4 cores
 *     - [ ] Implement Multi-threading per connection
 *     - [ ] Implement Dedicated thread to perform Live Performance Monitoring
 *     - [ ] Implement Digest Authentication for calls to server
 *     - [x] Implement Custom Options
 *     - [x] Implement TLS/HTTPS
**/

#include "ServerOptions.hpp"  // ServerOptions struct
#include "Resources.hpp"      // Resource endpoints
#include "Data.hpp"           // Raw key & Raw cert

#include <httpserver.hpp>     // libhttpserver
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <string>

int main() {

    // Create utopia-server using server options variables
    ServerOptions so;
    create_webserver cw = create_webserver(so.Port())
#ifndef NDEBUG
        .debug()
#endif // DEBUG
        .use_ssl()
        .connection_timeout(so.Timeout())
        .max_connections(so.MaxConnections())
        .max_threads(so.MaxThreads())
        .memory_limit(so.MemoryLimit());

    // Set server crt
    if (std::filesystem::is_regular_file(so.MemCert())) {
        cw.https_mem_cert(so.MemCert());
    } else {
        cw.raw_https_mem_cert(data::raw_mem_cert);
    }

    // Set server key
    if (std::filesystem::is_regular_file(so.MemKey())) {
        cw.https_mem_key(so.MemKey());
    } else {
        cw.raw_https_mem_key(data::raw_mem_key);
    }

    // Create and set resource endpoints
    webserver ws = cw;

    root_resource root_res;
    ws.register_resource("/", &root_res);
    hello_resource hw_res;
    ws.register_resource("/hello", &hw_res);

    std::cout << "Started server with options:\n" << so << std::endl;
    ws.start(true);

    return 0;
}
