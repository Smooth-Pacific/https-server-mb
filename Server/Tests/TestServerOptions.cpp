#include "TestServerOptions.hpp"
#include "ServerOptions.hpp"

#include <cassert>
#include <cstring>

void test_server_options_empty_environment() {

    // Store environment variables in ServerOptions struct
    ServerOptions so; 

    assert(!strncmp(so.HostAddr(), "127.0.0.1", 9));
    assert(so.Port() == 8080);

    assert(so.InternetProtocol() == IPV4_PROTOCOL);
    assert(so.Timeout()          == 60);
    assert(so.MaxConnections()   == 255);
    assert(so.MaxThreads()       == 8);
    assert(so.ThreadCount()      == 4); // TODO: Change to $n_proc
    assert(so.MemoryLimit()      == 32768);

}

void test_server_options_set_environment() {

    // Store environment variables in ServerOptions struct
    ServerOptions so; 

    assert(!strncmp(so.HostAddr(), "127.0.0.1", 9));
    assert(so.Port() == 8080);

    assert(so.InternetProtocol() == IPV4_PROTOCOL);
    assert(so.Timeout()          == 30);
    assert(so.MaxConnections()   == 127);
    assert(so.MaxThreads()       == 8);
    assert(so.ThreadCount()      == 4); // TODO: Change to $n_proc
    assert(so.MemoryLimit()      == 32768);

}
