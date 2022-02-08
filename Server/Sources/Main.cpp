/**
 * Creator:    VPR
 * Created:    January 27th, 2022
 * Updated:    February 1st, 2022
 *
 * Description:
 *     - [x] Implement client-server model
**/

#include <httpserver.hpp>
#include <iostream>
#include <cstdlib>

using namespace httpserver;

class resource : public http_resource {

  public: // http_resource overloads
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Testing."));
    }

};

int main() {

    // Get environment variables
    uint16_t port = std::getenv("PORT") ? static_cast<uint16_t>(std::strtoul(std::getenv("PORT"), nullptr, 10)) : 8080u;
    std::string mem_cert = std::getenv("MEM_CRT") ? std::getenv("MEM_CRT") : "resources/dummy.crt";
    std::string mem_key = std::getenv("MEM_KEY") ? std::getenv("MEM_KEY") : "resources/dummy.key";

    // DEBUG
    std::cout << "mem_cert: " << mem_cert << std::endl;
    std::cout << "mem_key: " << mem_key << std::endl;

    // Create web-server model using environment variables
    webserver ws = create_webserver(port)
#ifdef DEBUG
                   .debug()
#endif
                   .use_ssl()
                   .https_mem_cert(mem_cert)
                   .https_mem_key(mem_key);

    // Set content
    resource res;
    ws.register_resource("/hello", &res);

    // Start server
    std::cout << "Starting server on localhost:" << port << "...\n" << std::flush;
    ws.start(true);

    return 0;
}
