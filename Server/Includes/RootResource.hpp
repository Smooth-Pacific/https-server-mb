#ifndef ROOT_RESOURCE
#define ROOT_RESOURCE

#include <httpserver.hpp>

#ifndef MY_OPAQUE
#define MY_OPAQUE "11733b200778ce33060f31c9af70a870ba96ddd4" // Not sure what this is for
#endif

using namespace httpserver;

class root_resource : public http_resource {
private:
    std::string user = "username";
    std::string pass = "password";
public: // http_resource overloads
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Welcome to the Utopia Server."));
    }
    const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request& req) {
        if (req.get_digested_user() != user) {
            return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", MY_OPAQUE, true));
        } else {
            bool reload_nonce = false;
            if (!req.check_digest_auth("test@example.com", pass, 300, &reload_nonce)) {
                return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", MY_OPAQUE, reload_nonce));
            }
        }
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("SUCCESS", 200, "text/plain"));
    }
};

#endif // ROOT_RESOURCE
