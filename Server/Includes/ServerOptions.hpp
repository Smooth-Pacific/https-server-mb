#ifndef SERVER_OPTIONS_HEADER
#define SERVER_OPTIONS_HEADER

#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

#ifndef IPV4_PROTOCOL
#define IPV4_PROTOCOL 0
#endif // IPV4_PROTOCOL

#ifndef IPV6_PROTOCOL
#define IPV6_PROTOCOL 1
#endif // IPV6_PROTOCOL

#ifndef KILOBYTE
#define KILOBYTE 1024
#endif // KILOBYTE

struct ServerOptions {
  private: // Member variables
    bool            internet_protocol :  8;    // 0 for IPV4 and 1 for IPV6
    uint32_t        max_connections   :  8;    // Maximum connections supported by each thread
    uint32_t        max_threads       :  8;    // Maximum number of threads that the server will sustain
    uint32_t        n_threads         :  8;    // Number of threads the server will start with
    uint16_t        port              : 16;    // Port number for the server to bind to
    int32_t        timeout            : 32;    // Time in seconds that the server will wait before refusing connections
    int32_t        memory_limit       : 32;    // Time in seconds that the server will wait before refusing connections
    std::string     mem_cert;                  // Path to public server crt
    std::string     mem_key;                   // Path to private server key
  public: // Constructors
    ServerOptions()
        : internet_protocol(IPV4_PROTOCOL)
        , max_connections(255)
        , max_threads(std::thread::hardware_concurrency())
        , n_threads(1)
        , port(8080)
        , timeout(60)
        , memory_limit(32 * KILOBYTE)
    {
        internet_protocol = SetServerOption<bool, 2>(internet_protocol, "INTERNET_PROTOCOL");
        max_connections   = SetServerOption<uint32_t, 10>(max_connections, "MAX_CONNECTIONS");
        max_threads       = SetServerOption<uint32_t, 10>(max_threads, "MAX_THREADS"); // possible replace with hardware
        n_threads         = SetServerOption<uint32_t, 10>(n_threads, "N_THREADS");
        port              = SetServerOption<uint16_t, 10>(port, "PORT");
        timeout           = SetServerOption<int32_t, 10>(timeout, "TIMEOUT");
        memory_limit      = SetServerOption<int32_t, 10>(memory_limit, "MEMORY_LIMIT");
        mem_cert          = SetServerOption<std::string>(mem_cert, "MEM_CERT");
        mem_key           = SetServerOption<std::string>(mem_key, "MEM_KEY");

        // Validate options
        ValidateMaxConnections();
        ValidateMaxThreads();
        ValidateNumberOfThreads();
        ValidatePort();
        ValidateTimeout();
        ValidateMemoryLimit();
    }
  private: // Helper functions
    template <typename T>
    T SetServerOption(T& server_option, const char* env_variable) {
        char* result;
        if ((result = std::getenv(env_variable)) != NULL) {
            try { 
                return static_cast<T>(std::getenv(env_variable));
            } catch (...) {
                std::cerr << "Fatal error: failed to set environment variable" << std::endl;
                exit(-1);
            }
        } else {
            return server_option;
        }
    }
    template <typename T, unsigned int base>
    T SetServerOption(T server_option, const char* env_variable) {
        char* result;
        if ((result = std::getenv(env_variable)) != NULL) {
            try {
                return static_cast<T>(std::strtoul(std::getenv(env_variable), nullptr, base));
            } catch (...) {
                std::cerr << "Fatal error: failed to set environment variable" << std::endl;
                exit(-1);
            }
        } else {
            return server_option;
        }
    }

    void ValidateMaxConnections() const {
        if (max_connections < 0 || max_connections > 255) {
            std::cerr << "Initialization error: MAX_CONNECTIONS\n"
                         "\n"
                         "  Environment variable 'MAX_CONNECTIONS='" << max_connections << " is out of\n"
                         "  range. Please use a value between 0 and 255.\n";
            exit(1);
        }
    }
    void ValidateMaxThreads() const {
        if (max_threads < 1 || max_threads > std::thread::hardware_concurrency()) {
            std::cerr << "Initialization error: MAX_THREADS\n"
                         "\n"
                         "  Environment variable 'MAX_THREADS='" << max_threads << " is out of\n"
                         "  range. Please use a value between 1 and "  << std::thread::hardware_concurrency() << ".\n";
            exit(1);
        }
    }
    void ValidateNumberOfThreads() const {
        if (n_threads < 1 || n_threads > std::thread::hardware_concurrency() - 1) {
            std::cerr << "Initialization error: N_THREADS\n"
                         "\n"
                         "  Environment variable 'N_THREADS='" << n_threads << " is out of\n"
                         "  range. Please use a value between 1 and "  << std::thread::hardware_concurrency()-1 << ".\n";
            exit(1);
        }
    }
    void ValidatePort() const {
        if (port < 1023 || port > 65535) {
            std::cerr << "Initialization error: PORT\n"
                         "\n"
                         "  Environment variable 'PORT='" << port << " is out of\n"
                         "  range. Please use a value between 1024 and "  << 65535 << ".\n";
            exit(1);
        }
    }
    void ValidateTimeout() const {
        if (timeout < 0 || timeout > 600) {
            std::cerr << "Initialization error: TIMEOUT\n"
                         "\n"
                         "  Environment variable 'TIMEOUT='" << timeout << " is out of\n"
                         "  range. Please use a value between 0 and "  << 600 << ".\n";
            exit(1);
        }
    }
    void ValidateMemoryLimit() const {
        auto pages = sysconf(_SC_PHYS_PAGES);
        auto page_size = sysconf(_SC_PAGE_SIZE);
        auto total_memory = pages * page_size;
        if (memory_limit < 0 || memory_limit >= total_memory) {
            std::cerr << "Initialization error: MEMORY_LIMIT\n"
                         "\n"
                         "  Environment variable 'MEMORY_LIMIT='" << memory_limit << " is out of\n"
                         "  range. Please use a value between 32768 and "  << total_memory << ".\n";
            exit(1);
        }
    }
  public: // Constant functions
    bool        InternetProtocol() const { return internet_protocol; };
    uint16_t    MaxConnections()   const { return max_connections; };
    uint16_t    MaxThreads()       const { return max_threads; };
    uint16_t    ThreadCount()      const { return n_threads; };
    uint16_t    Port()             const { return port; };
    int32_t     Timeout()         const { return timeout; };
    int32_t     MemoryLimit()     const { return memory_limit; };
    const char* MemCert()          const { return mem_cert.c_str(); };
    const char* MemKey()           const { return mem_key.c_str(); };
  public: // Friend functions
    friend std::ostream& operator << (std::ostream& os, const ServerOptions& so) {
        os << "Host Address:\t\t"       << (so.internet_protocol == IPV4_PROTOCOL ? "127.0.0.1" : "0000:0000:0000:0000:0000:0000:0000:0001") << "\n";
        os << "Port:\t\t\t"             << so.port << "\n";
        os << "\n";
        os << "Internet Protocol:\t"    << (so.internet_protocol == IPV4_PROTOCOL ? "IPV4" : "IPV6") << "\n";
        os << "Max Connections:\t"      << so.max_connections << "\n";
        os << "Max Threads:\t\t"        << so.max_threads << "\n";
        os << "Threads Count:\t\t"      << so.n_threads << "\n";
        os << "Timeout:\t\t"            << so.timeout << "\n";
        os << "Memory Limit (bytes):\t" << so.memory_limit << "\n";

        return os;
    }
};

#endif // SERVER_OPTIONS_HEADER
