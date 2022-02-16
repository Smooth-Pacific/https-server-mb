#ifndef SERVER_OPTIONS_HEADER
#define SERVER_OPTIONS_HEADER

#include <iostream>
#include <string>

#ifndef IPV4_PROTOCOL
#define IPV4_PROTOCOL 0
#endif // IPV4_PROTOCOL

#ifndef IPV6_PROTOCOL
#define IPV6_PROTOCOL 1
#endif // IPV6_PROTOCOL

struct ServerOptions {
  private: // Member variables
    bool            internet_protocol : 8;    // 0 for IPV4 and 1 for IPV6
    unsigned        max_connections   : 8;    // Maximum connections supported by each thread
    unsigned        max_threads       : 8;    // Maximum number of threads that the server will sustain
    unsigned        n_threads         : 8;    // Number of threads the server will start with
    uint16_t        port              : 16;   // Port number for the server to bind to
    uint64_t        timeout_ms        : 64;   // Time in milliseconds that the server will wait before refusing connections
    std::string     host_addr;                // Host address in IP form (i.e. 127.0.0.1)
  public: // Constructors
    ServerOptions()
        : internet_protocol(false)
        , max_connections(255)
        , max_threads(8)
        , n_threads(4)
        , port(8080)
        , timeout_ms(60000)
        , host_addr("127.0.0.1")
    {
        internet_protocol = SetServerOption<bool, 2>(internet_protocol, "INTERNET_PROTOCOL");
        max_connections   = SetServerOption<uint8_t, 10>(max_connections, "MAX_CONNECTIONS");
        max_threads       = SetServerOption<uint8_t, 10>(max_threads, "MAX_THREADS");
        n_threads         = SetServerOption<uint8_t, 10>(n_threads, "N_THREADS");
        port              = SetServerOption<uint16_t, 10>(port, "PORT");
        timeout_ms        = SetServerOption<uint64_t, 10>(timeout_ms, "TIMEOUT_MS");
        host_addr         = SetServerOption<std::string>(host_addr, "HOST");
    }
  private: // Helper functions
    template <typename T>
    T SetServerOption(T& server_option, const char* env_variable) {
        char* result;
        if ((result = std::getenv(env_variable)) != NULL) {
            return static_cast<T>(std::getenv(env_variable));
        } else {
            return server_option;
        }
    }
    template <typename T, unsigned int base>
    T SetServerOption(T server_option, const char* env_variable) {
        char* result;
        if ((result = std::getenv(env_variable)) != NULL) {
            return static_cast<T>(std::strtoul(std::getenv(env_variable), nullptr, base));
        } else {
            return server_option;
        }
    }
  public: // Constant functions
    bool            InternetProtocol() const { return internet_protocol; };
    uint16_t        MaxConnections() const   { return max_connections; };
    uint16_t        MaxThreads() const       { return max_threads; };
    uint16_t        Port() const             { return port; };
    uint64_t        TimeoutMs() const        { return timeout_ms; };
    const char*     HostAddr() const         { return host_addr.c_str(); };
  public: // Friend functions
    friend std::ostream& operator << (std::ostream& os, const ServerOptions& so) {
        os << "Host Address:\t\t"    << so.host_addr.c_str() << "\n";
        os << "Port:\t\t\t"          << so.port << "\n";
        os << "\n";
        os << "Internet Protocol:\t" << (so.internet_protocol == IPV4_PROTOCOL ? "IPV4" : "IPV6") << "\n";
        os << "Max Connections:\t"   << so.max_connections << "\n";
        os << "Max Threads:\t\t"     << so.max_threads << "\n";
        os << "Timeout (ms):\t\t"    << so.timeout_ms << "\n";

        return os;
    }
};

#endif // SERVER_OPTIONS_HEADER
