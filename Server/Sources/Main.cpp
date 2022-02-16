/**
 * Creator:    VPR
 * Created:    January 27th, 2022
 * Updated:    February 16th, 2022
 *
 * Description:
 *     - [ ] Implement Thread Pooling for CPUs with > 4 cores
 *     - [ ] Implement Multi-threading per connection
 *     - [ ] Implement Dedicated thread to perform Live Performance Monitoring
 *     - [ ] Implement Digest Authentication for calls to server
 *     - [x] Implement Custom Options
 *     - [x] Implement TLS/HTTPS
**/

#include "ServerOptions.hpp"  // ServerOptions struct
#include "Resources.hpp"      // Resource endpoints

#include <httpserver.hpp>     // libhttpserver
#include <iostream>
#include <cstdlib>
#include <string>

int main() {

    // Create Server Options struct
    ServerOptions so;
    // Create utopia-server using server options variables
    webserver ws = create_webserver(so.Port())
#ifndef NDEBUG
        .debug()
#endif // DEBUG
        .use_ssl()
        .https_mem_cert("/home/utopia/certs/server_ca/certs/smoothstack_server.crt")
        .https_mem_key("/home/utopia/certs/server_ca/private/smoothstack_server.key")
        .max_threads(so.MaxThreads());


    // Create and set resource endpoints
    root_resource root_res;
    hello_resource hw_res;
    ws.register_resource("/", &root_res);
    ws.register_resource("/hello", &hw_res);

    std::cout << "Started server with options:\n" << so << std::endl;
    ws.start(true);

    return 0;
}
