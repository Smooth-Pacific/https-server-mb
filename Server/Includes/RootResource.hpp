#ifndef ROOT_RESOURCE
#define ROOT_RESOURCE

#include <httpserver.hpp>

using namespace httpserver;

class root_resource : public http_resource {
  public: // http_resource overloads
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Welcome to the Utopia Server."));
    }
};

#endif // ROOT_RESOURCE
