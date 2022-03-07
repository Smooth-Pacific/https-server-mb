#ifndef HELLO_RESOURCE
#define HELLO_RESOURCE

#include "Logger.hpp"

#include <httpserver.hpp>

using namespace httpserver;

class hello_resource : public http_resource {
  public: // http_resource overloads
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Hello, World."));
    }
};

#endif // HELLO_RESOURCE
