#ifndef FILE_RESOURCE_HEADER
#define FILE_RESOURCE_HEADER

#include "Logger.hpp"

#include <httpserver.hpp>
#include <filesystem>

class file_resource : public httpserver::http_resource, public Logger {
private: // Private member variables
    std::string content_path;
    std::string content_type;
public: // Constructors
    file_resource()
        : content_path("static/example.txt")
        , content_type("text/plain")
    {
    }
    file_resource(std::string path, std::string type)
        : content_path(path)
        , content_type(type)
    {
    }
public: // GET, PUT, POST, DELETE requests
    const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request& req) {
        custom_log_access(req);
        return std::shared_ptr<httpserver::file_response>(new httpserver::file_response(content_path, 200, content_type));
    }
    const std::shared_ptr<httpserver::http_response> render_PUT(const httpserver::http_request& req) {
        custom_log_access(req);

        // overwrite?
        std::ofstream ofs(req.get_user() + "_test_file.txt");

        // proper name/path/etc

        if (req.content_too_large()) {
            log_failure(req);
            return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Idk either bro", 400));
        } else {
            ofs << req.get_content();
            ofs.close();
        }

        log_success(req);
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Filed saved", 200));
    }
    const std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request& req) {
        custom_log_access(req);

        // overwrite?
        std::ofstream ofs(req.get_user() + "_test_file.txt", std::ios::app);

        // proper name/path/etc

        if (req.content_too_large()) {
            log_failure(req);
            return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Idk either bro", 400));
        } else {
            ofs << req.get_content();
            ofs.close();
        }

        log_success(req);
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Filed saved.", 200));
    }
    const std::shared_ptr<httpserver::http_response> render_DELETE(const httpserver::http_request& req) {
        custom_log_access(req);

        std::string target = (req.get_user() + "_test_file.txt");
        if (std::filesystem::is_regular_file(target)) {
            auto deleted = std::filesystem::remove(target);
            if (!deleted) {
                log_failure(req);
                return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Failed to delete file.", 403));
            } 
        } else {
            log_failure(req);
            return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("File does not exist.", 404));
        }

        log_success(req);
        return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Filed deleted.", 200));
    }
};

#endif // FILE_RESOURCE_HEADER
