#ifndef SERVER_OPTIONS_HEADER
#define SERVER_OPTIONS_HEADER

#include <iostream>
#include <thread>
#include <string>

#ifndef IPV4_PROTOCOL
#define IPV4_PROTOCOL 0
#endif // IPV4_PROTOCOL

#ifndef IPV6_PROTOCOL
#define IPV6_PROTOCOL 1
#endif // IPV6_PROTOCOL

#ifndef KILOBYTE
#define KILOBYTE 1024
#endif // KILOBYTE

#ifndef MEGABYTE
#define MEGABYTE KILOBYTE * KILOBYTE
#endif // MEGABYTE

#ifndef THREAD_FACTOR
#define THREAD_FACTOR 4
#endif // THREAD_FACTOR

struct ServerOptions {
private: // Member variables
    bool            internet_protocol       :  4;    // 0 for IPV4 and 1 for IPV6
    bool            dual_stack_enabled      :  4;    // Allow IPV4 and IPV6 connectivity
    uint32_t        max_connections         :  8;    // Maximum connections supported by each thread
    uint32_t        max_threads             :  8;    // Maximum number of threads that the server will sustain
    uint32_t        n_threads               :  8;    // Number of threads the server will start with
    uint16_t        per_IP_connection_limit : 16;    // Number of concurrent connections allowed per IP address
    uint16_t        port                    : 16;    // Port number for the server to bind to
    uint32_t        content_size_limit      : 32;    // Limit of content size (KB) allowed to be handled by the server
    int32_t         timeout                 : 32;    // Time in seconds that the server will wait before refusing connections
    int32_t         memory_limit            : 32;    // Memory limit :)
    int32_t         max_thread_stack_size   : 32;    // TODO
    std::string     mem_cert;                        // Path to public server crt
    std::string     mem_key;                         // Path to private server key
public: // Constructors
    ServerOptions()
        : internet_protocol(IPV4_PROTOCOL)
        , dual_stack_enabled(false)
        , max_connections(255)
        , max_threads(std::thread::hardware_concurrency() * THREAD_FACTOR)
        , n_threads(2)
        , per_IP_connection_limit(10)
        , port(8080)
        , content_size_limit(64 * MEGABYTE)
        , timeout(60)
        , memory_limit(32 * KILOBYTE)
        , max_thread_stack_size(0)
    {
        internet_protocol       = SetServerOption<bool, 2>(internet_protocol, "INTERNET_PROTOCOL");
        dual_stack_enabled      = SetServerOption<bool, 2>(dual_stack_enabled, "USE_DUAL_STACK");
        max_connections         = SetServerOption<uint32_t, 10>(max_connections, "MAX_CONNECTIONS");
        max_threads             = SetServerOption<uint32_t, 10>(max_threads, "MAX_THREADS");
        n_threads               = SetServerOption<uint32_t, 10>(n_threads, "N_THREADS");
        per_IP_connection_limit = SetServerOption<uint16_t, 10>(per_IP_connection_limit, "PER_CONNECTION_IP");
        port                    = SetServerOption<uint16_t, 10>(port, "PORT");
        content_size_limit      = SetServerOption<uint32_t, 10>(content_size_limit, "CONTENT_SIZE_LIMIT");
        timeout                 = SetServerOption<int32_t, 10>(timeout, "TIMEOUT");
        memory_limit            = SetServerOption<int32_t, 10>(memory_limit, "MEMORY_LIMIT");
        max_thread_stack_size   = SetServerOption<int32_t, 10>(max_thread_stack_size, "MAX_THREAD_STACK_SIZE");
        mem_cert                = SetServerOption<std::string>(mem_cert, "MEM_CERT");
        mem_key                 = SetServerOption<std::string>(mem_key, "MEM_KEY");

        // Validate options
        ValidateMaxConnections();
        ValidateMaxThreads();
        ValidateNumberOfThreads();
        ValidatePort();
        ValidateTimeout();
        ValidateMemoryLimit();
    }
private: // Helper functions
    template <typename T> [[nodiscard]]
    inline T SetServerOption(T& server_option, const char* env_variable) {
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
    template <typename T, unsigned int base> [[nodiscard]]
    inline T SetServerOption(T server_option, const char* env_variable) {
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
private: // Constant helper functions
    void        ValidateMaxConnections()  const;
    void        ValidateMaxThreads()      const;
    void        ValidateNumberOfThreads() const;
    void        ValidatePort()            const;
    void        ValidateTimeout()         const;
    void        ValidateMemoryLimit()     const;
public: // Constant functions
    bool        InternetProtocol()        const;
    bool        DualStackEnabled()        const;
    uint16_t    MaxConnections()          const;
    uint16_t    MaxThreads()              const;
    uint16_t    ThreadCount()             const;
    uint16_t    PerIpConnectionLimit()    const;
    uint16_t    Port()                    const;
    int32_t     Timeout()                 const;
    int32_t     MemoryLimit()             const;
    uint32_t    ContentSizeLimit()        const;
    int32_t     MaxThreadStackSize()      const;
    const char* MemCert()                 const;
    const char* MemKey()                  const;
public: // Friend functions
    friend std::ostream& operator << (std::ostream& os, const ServerOptions& so);
};

#endif // SERVER_OPTIONS_HEADER
