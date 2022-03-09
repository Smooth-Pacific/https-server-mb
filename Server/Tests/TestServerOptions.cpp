#include "TestServerOptions.hpp"
#include "ServerOptions.hpp"

#include <cassert>
#include <cstring>

[[nodiscard]]
bool test_server_options_empty_environment() {

    // Store environment variables in ServerOptions struct
    ServerOptions so; 

    assert(so.InternetProtocol()     == IPV4_PROTOCOL);
    assert(so.DualStackEnabled()     == false);
    assert(so.Port()                 == 8080);

    assert(so.MaxThreadStackSize()   == 0);
    assert(so.MaxThreads()           == std::thread::hardware_concurrency() * THREAD_FACTOR);
    assert(so.ThreadCount()          == 2);
    assert(so.ContentSizeLimit()     == 64 * MEGABYTE);
    assert(so.PerIpConnectionLimit() == 10);
    assert(so.MaxConnections()       == 255);
    assert(so.MemoryLimit()          == 32 * KILOBYTE);
    assert(so.Timeout()              == 60);

    return true;
}

[[nodiscard]]
bool test_server_options_set_environment() {

    // Store environment variables in ServerOptions struct
    ServerOptions so; 

    assert(so.InternetProtocol()     == IPV6_PROTOCOL);
    assert(so.DualStackEnabled()     == true);
    assert(so.Port()                 == 8081);

    assert(so.MaxThreadStackSize()   == 0);
    assert(so.MaxThreads()           == std::thread::hardware_concurrency() * THREAD_FACTOR);
    assert(so.ThreadCount()          == std::thread::hardware_concurrency() - 1);
    assert(so.ContentSizeLimit()     == 100 * MEGABYTE);
    assert(so.PerIpConnectionLimit() == 10);
    assert(so.MaxConnections()       == 127);
    assert(so.MemoryLimit()          == 32 * KILOBYTE);
    assert(so.Timeout()              == 30);

    return true;
}
