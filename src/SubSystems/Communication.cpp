#include <SubSystems/Communication.hpp>
#include <Properties.hpp>

#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

SubSystems::Communication::Command SubSystems::Communication::command;

int timeoutMicros; // Communication timeout in microseconds

int socketFD;           // Socket file descriptor
sockaddr_in socketAddr; // Socket address INET

int gsPort;             // Ground station port
char gsIPAddress[16]{}; // Ground station IP address

void start_connection() noexcept;
void communicate() noexcept;
bool create_socket() noexcept;

void SubSystems::Communication::initialize()
{
    log_function_call();

    try
    {
        // Copy the communication timeout delay from the properties
        timeoutMicros = Properties::get_int("subsystems_communication_timeout_micros");

        // Copy the ground station's IP address from the properties
        const std::string ip{Properties::get_string("subsystems_communication_gs_ip_address")};
        memcpy(gsIPAddress, ip.data(), ip.length());

        // Copy the ground station's port from the properties
        gsPort = Properties::get_int("subsystems_communication_gs_port");

        info("Ground station is at %s:%d" ENDL "Set timeout to %dμs", gsIPAddress, gsPort, timeoutMicros);
    }
    catch (const std::exception &ex)
    {
        log_catch_and_throw_exception();
        throw ex;
    }
}

void SubSystems::Communication::run() noexcept
{
    log_function_call();

    std::thread thread([&] {
        while (command != Command::Terminate)
        {
            info("Attempting to connect to the ground station...");

            start_connection();
            communicate();
            cleanup();
        }
    });
    thread.detach();
}

void SubSystems::Communication::cleanup() noexcept
{
    close(socketFD);
}

void start_connection() noexcept
{
    while (true)
    {
        if (!create_socket())
        {
            usleep(timeoutMicros);
            continue;
        }

        // Attempt to connect the socket file descriptor to the socket address
        if (connect(socketFD, (sockaddr *)&socketAddr, sizeof(socketAddr)))
        {
            SubSystems::Communication::cleanup();
            usleep(timeoutMicros);
            continue;
        }
        else
        { // If succeeded, break the loop.
            info("Connected to the ground station!");
            break;
        }
    }
}

void communicate() noexcept
{
    using Communication = SubSystems::Communication;
    using Command = Communication::Command;

    ssize_t bytes;
    uint8_t buffer[1024];

    while (Communication::command != Command::Terminate)
    {
        std::fill(std::begin(buffer), std::end(buffer), 0);

        bytes = read(socketFD, buffer, sizeof(buffer));
        if (bytes <= 0)
        { 
            info("Lost connection with the ground station!");
            break;
        }
        else
        {
            uint8_t packetId = buffer[0];
            verbose("Received packet with ID = %d", packetId);

            switch (packetId)
            {
            case uint8_t(Command::Terminate):
                warn(BOLD "Terminating!");
                Communication::command = Command::Terminate;
            default:
                break;
            }
        }
    }
}

bool create_socket() noexcept
{
    { // Create the socket file descriptor.
        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD == -1)
        {
            // log("client.create_socket().socket() has failed: %s\n", strerror(errno));
            return false;
        }
    }

    { // Initialize the server address.
        socketAddr.sin_family = AF_INET;
        socketAddr.sin_port = htons(gsPort);

        int ret = inet_pton(AF_INET, gsIPAddress, &socketAddr.sin_addr.s_addr);
        if (ret == 0 || ret == -1)
        {
            return false;
        }
    }

    if (timeoutMicros > 0)
    { // Set the socket timeout
        const timeval timeout = {timeoutMicros / 1000000, timeoutMicros % 1000000};
        if (setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO | SO_SNDTIMEO, &timeout, sizeof(timeval)))
        {
            // log("client.create_socket().setsockopt() has failed: %s\n", strerror(errno));
            return false;
        }
    }

    return true;
}