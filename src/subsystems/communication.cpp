#include <subsystems/communication.hpp>
#include <properties.hpp>
#include <logger.hpp>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>

int timeoutMicros; // Communication timeout in microseconds

int socketFd;           // Socket file descriptor
sockaddr_in socketAddr; // Socket address INET

int gsPort;           // Ground station port
char gsIPAddress[16]; // Ground station IP address

void SubSystems::Communication::initialize()
{
    print_function_call();

    try
    {
        // Copy the communication timeout delay from the properties
        timeoutMicros = Properties::get_int("subsystems_communication_timeout_micros");
        // Copy the ground station's IP address from the properties
        strcpy(gsIPAddress, Properties::get_string("subsystems_communication_gs_ip_address").data());
        // Copy the ground station's port from the properties
        gsPort = Properties::get_int("subsystems_communication_gs_port");
    }
    catch (const std::exception &ex)
    {
        print_catch_and_throw_exception();
        throw ex;
    }
}

void SubSystems::Communication::cleanup() noexcept
{
    print_function_call();
}