#ifndef MIME_RESOURCE_HEADER
#define MIME_RESOURCE_HEADER

#include "Authorization.hpp"
#include "Logger.hpp"

#include <httpserver.hpp>

using namespace httpserver;

class mime_resource : public http_resource, public Authorization {
public: // http_resource overloads
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Welcome to the Utopia Server."));
    }
    const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request& req) {
        if (req.get_digested_user() != Username()) {
            return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), true));
        } else {
            bool reload_nonce = false;
            if (!req.check_digest_auth("test@example.com", Password(), 300, &reload_nonce)) {
                return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), reload_nonce));
            }
        }
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("SUCCESS", 200, "text/plain"));
    }
    // TODO PUT
    const std::shared_ptr<httpserver::http_response> render_PUT(const httpserver::http_request& req) {
        if (req.get_digested_user() != Username()) {
            return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), true));
        } else {
            bool reload_nonce = false;
            if (!req.check_digest_auth("test@example.com", Password(), 300, &reload_nonce)) {
                return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), reload_nonce));
            }
        }
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("SUCCESS", 200, "text/plain"));
    }
    // TODO POST
    const std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request& req) {
        if (req.get_digested_user() != Username()) {
            return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), true));
        } else {
            bool reload_nonce = false;
            if (!req.check_digest_auth("test@example.com", Password(), 300, &reload_nonce)) {
                return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), reload_nonce));
            }
        }
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("SUCCESS", 200, "text/plain"));
    }
    // TODO DELETE
    const std::shared_ptr<httpserver::http_response> render_DELETE(const httpserver::http_request& req) {
        if (req.get_digested_user() != Username()) {
            return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), true));
        } else {
            bool reload_nonce = false;
            if (!req.check_digest_auth("test@example.com", Password(), 300, &reload_nonce)) {
                return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), reload_nonce));
            }
        }
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("SUCCESS", 200, "text/plain"));
    }
};

#endif // MIME_RESOURCE_HEADER
