#include <client.hpp>
#include <logger.hpp>

#include <sys/socket.h>
#include <unistd.h>

#include <thread>
#include <chrono>
#include <string>
#include <iostream>

int         Client::socketFD;
sockaddr_in Client::socketAddress;

int Client::initialize() noexcept
{
    return 0;
}

int Client::run() noexcept
{
    int err = 0;
    while (true)
    {
        err = start_connection();
        if (err)
        {
            log << "client.start_connection() has failed with code " << err << "!\n";
            return err;
        }

        err = communicate();
        if (err)
        {
            log << "client.communicate() has failed with code " << err << "!\n";
            return err;
        }

        cleanup();
    }
    return err;
}

inline int Client::start_connection() noexcept
{
    log << "Attempting to connect to the ground station!\n";

    int err = create_socket();
    if (err)
    {
        log << "client.create_socket() has failed with code " << err << "!\n";
        return err;
    }

    while (true) 
    {
        // If connection has failed, reopen the socket and retry
        if (!connect(socketFD, (sockaddr*)&socketAddress, sizeof(socketAddress))) 
        {
            close(socketFD);
            create_socket();
        } 
        else 
        {
            break;
        }
    }

    

    return err;
}

inline int Client::communicate() noexcept
{
    return 0;
}

inline void Client::cleanup() noexcept
{
}

inline int Client::create_socket() noexcept
{
    return 0;
}