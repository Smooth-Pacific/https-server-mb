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
  public:
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Testing."));
    }
};

int main() {

    // Create webserver model using environment variables
    webserver ws = []{
        uint16_t port = 8080;
        if (auto tmp = getenv("PORT")) {
            port = static_cast<uint16_t>(std::strtoul(tmp, nullptr, 10));
        }
        return create_webserver(port);
    }();

    test_resource res;
    ws.register_resource("/hello", &res);

    std::cout << "Starting server on localhost:" << 8080 << "...\n" << std::flush;
    ws.start(true);

    return 0;
}
