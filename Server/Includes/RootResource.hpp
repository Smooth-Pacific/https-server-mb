#ifndef ROOT_RESOURCE_HEADER
#define ROOT_RESOURCE_HEADER

#include "Authorization.hpp"
#include "Logger.hpp"

#include <httpserver.hpp>

#ifndef NDEBUG
#include <chrono>
#include <thread>
#endif // NDEBUG

using namespace httpserver;

class root_resource : public http_resource, public Authorization, public Logger {
public: // http_resource overloads
    const std::shared_ptr<http_response> render(const http_request& req) {
        custom_log_access(req);
        return std::shared_ptr<http_response>(new string_response("Welcome to the Utopia Server."));
    }
    const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request& req) {
#ifndef NDEBUG
        //std::this_thread::sleep_for(std::chrono::milliseconds(500u));
#endif // NDEBUG

        if (req.get_digested_user() != Username()) {
            log_failure(req);
            return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), true));
        } else {
            bool reload_nonce = false;
            if (!req.check_digest_auth("test@example.com", Password(), 300, &reload_nonce)) {
                log_failure(req);
                return std::shared_ptr<httpserver::digest_auth_fail_response>(new httpserver::digest_auth_fail_response("FAIL", "test@example.com", Opaque(), reload_nonce));
            }
        }
        log_success(req);
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

#endif // ROOT_RESOURCE_HEADER
