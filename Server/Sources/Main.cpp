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

class test_resource : public http_resource
{
  public: // http_resource overloads
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Testing."));
    }
};

int main() {

    // Create web-server model using environment variables
    uint16_t port = getenv("PORT") ? static_cast<uint16_t>(std::strtoul(getenv("PORT"), nullptr, 10)) : 8080u;
    webserver ws = create_webserver(port);

    test_resource res;
    ws.register_resource("/", &res);

    std::cout << "Starting server on localhost:" << port << "...\n" << std::flush;
    ws.start(true);

    return 0;
}
