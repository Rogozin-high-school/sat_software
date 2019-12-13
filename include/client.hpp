#pragma once

#include <arpa/inet.h>

class Client {
public:
    static int initialize() noexcept;
    static int run() noexcept;
private:
    static int socketFD;
    static sockaddr_in socketAddress;

    static int start_connection() noexcept;
    static int communicate() noexcept;
    static void cleanup() noexcept;
    
    static int create_socket() noexcept;
};