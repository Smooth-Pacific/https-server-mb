#include "ServerOptions.hpp"

#include <unistd.h>

void ServerOptions::ValidateMaxConnections() const {
    if (max_connections < 0 || max_connections > 255) {
        std::cerr << "Initialization error: MAX_CONNECTIONS\n"
                     "\n"
                     "  Environment variable 'MAX_CONNECTIONS='" << max_connections << " is out of\n"
                     "  range. Please use a value between 0 and 255.\n";
        exit(1);
    }
}

void ServerOptions::ValidateMaxThreads() const {
    if (max_threads < 1 || max_threads > std::thread::hardware_concurrency() * THREAD_FACTOR) {
        std::cerr << "Initialization error: MAX_THREADS\n"
                     "\n"
                     "  Environment variable 'MAX_THREADS='" << max_threads << " is out of\n"
                     "  range. Please use a value between 1 and "  << std::thread::hardware_concurrency() << ".\n";
        exit(1);
    }
}

void ServerOptions::ValidateNumberOfThreads() const {
    if (n_threads < 1 || n_threads > std::thread::hardware_concurrency() - 1) {
        std::cerr << "Initialization error: N_THREADS\n"
                     "\n"
                     "  Environment variable 'N_THREADS='" << n_threads << " is out of\n"
                     "  range. Please use a value between 1 and "  << std::thread::hardware_concurrency()-1 << ".\n";
        exit(1);
    }
}

void ServerOptions::ValidatePort() const {
    if (port < 1023 || port > 65535) {
        std::cerr << "Initialization error: PORT\n"
                     "\n"
                     "  Environment variable 'PORT='" << port << " is out of\n"
                     "  range. Please use a value between 1024 and "  << 65535 << ".\n";
        exit(1);
    }
}

void ServerOptions::ValidateTimeout() const {
    if (timeout < 0 || timeout > 600) {
        std::cerr << "Initialization error: TIMEOUT\n"
                     "\n"
                     "  Environment variable 'TIMEOUT='" << timeout << " is out of\n"
                     "  range. Please use a value between 0 and "  << 600 << ".\n";
        exit(1);
    }
}

void ServerOptions::ValidateMemoryLimit() const {
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

bool        ServerOptions::InternetProtocol()     const { return internet_protocol; };
bool        ServerOptions::DualStackEnabled()     const { return dual_stack_enabled; };
uint16_t    ServerOptions::MaxConnections()       const { return max_connections; };
uint16_t    ServerOptions::MaxThreads()           const { return max_threads; };
uint16_t    ServerOptions::ThreadCount()          const { return n_threads; };
uint16_t    ServerOptions::PerIpConnectionLimit() const { return per_IP_connection_limit; }
uint16_t    ServerOptions::Port()                 const { return port; };
int32_t     ServerOptions::Timeout()              const { return timeout; };
int32_t     ServerOptions::MemoryLimit()          const { return memory_limit; };
uint32_t    ServerOptions::ContentSizeLimit()     const { return content_size_limit; };
int32_t     ServerOptions::MaxThreadStackSize()   const { return max_thread_stack_size; };
const char* ServerOptions::MemCert()              const { return mem_cert.c_str(); };
const char* ServerOptions::MemKey()               const { return mem_key.c_str(); };

std::ostream& operator << (std::ostream& os, const ServerOptions& so) {
    os << "Host Address\t\t: "            << (so.internet_protocol == IPV4_PROTOCOL ? "127.0.0.1" : "[::1]") << "\n";
    os << "Port\t\t\t: "                  << so.port << "\n";
    os << "\n";
    os << "Internet Protocol\t: "         << (so.internet_protocol == IPV4_PROTOCOL ? "IPV4" : "IPV6") << "\n";
    os << "Dual Stack\t\t: "              << (so.dual_stack_enabled ? "Enabled" : "Disabled") << "\n";
    os << "\n";

    if (so.max_thread_stack_size == 0) {
        os << "Max Thread Stack Size\t: " << "(System Default)"  << "\n";
    } else {
        os << "Max Thread Stack Size\t: " << so.max_thread_stack_size << "\n";
    }

    os << "Max Threads\t\t: "             << so.max_threads << "\n";
    os << "Thread Count\t\t: "            << so.n_threads << "\n";
    os << "\n";
    os << "Content Size Limit\t: "        << so.content_size_limit << " kilobytes\n";
    os << "Per Ip Connection Limit\t: "   << so.per_IP_connection_limit << "\n";
    os << "Max Connections\t\t: "         << so.max_connections << "\n";
    os << "Memory Limit\t\t: "            << so.memory_limit << " bytes\n";
    os << "Timeout\t\t\t: "               << so.timeout << "\n";

    return os;
}
