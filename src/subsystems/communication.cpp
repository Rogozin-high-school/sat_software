#include <subsystems/communication.hpp>
#include <properties.hpp>
#include <logger.hpp>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

enum class Intent : uint8_t
{
    None = 0x00,
    Terminate = 0xff
} intent;

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

    while (intent != Intent::Terminate)
    {
        start_connection();
        communicate();
        cleanup();
    }
}

void SubSystems::Communication::cleanup() noexcept
{
    // log_function_call();
}

void start_connection() noexcept
{
    // log_function_call();

    while (true)
    {
        if (!create_socket())
        {
            // log("client.start_connection().create_socket() has failed!\n");
            usleep(timeoutMicros);
            continue;
        }

        // Attempt to connect the socket file descriptor to the socket address
        if (connect(socketFD, (sockaddr *)&socketAddr, sizeof(socketAddr)))
        {
            // log("client.start_connection().connect() has failed: %s\n", strerror(errno));
            SubSystems::Communication::cleanup();
            usleep(timeoutMicros);
            continue;
        }
        else
        { // If succeeded, break the loop.
            // log("Connected to the ground station!\n");
            break;
        }
    }
}

void communicate() noexcept
{
    // log_function_call();

    ssize_t bytes;
    uint8_t buffer[1024];

    // log("Waiting for an initial packet...\n");

    while (intent != Intent::Terminate)
    {
        std::fill(std::begin(buffer), std::end(buffer), 0);

        bytes = read(socketFD, buffer, sizeof(buffer));
        if (bytes == -1)
        {
            // log("client.communicate().read() has failed: %s\n", strerror(errno));
        }
        else if (bytes == 0)
        {
            // log("client has received EOF!\n");
            break;
        }
        else
        {
            uint8_t packetId = buffer[0];
            // log("Received packet with ID = %d\n", packetId);
            switch (packetId)
            {
            case uint8_t(Intent::Terminate):
                // log("Received terminate packet!\n");
                intent = Intent::Terminate;
            default:
                break;
            }
        }
    }
}

bool create_socket() noexcept
{
    // log_function_call();

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
        if (ret == 0)
        {
            // log("client.create_socket().inet_pton() has failed: %s Bad address!\n", gsIPAddress);
            return false;
        }
        else if (ret == -1)
        {
            // log("client.create_socket().inet_pton() has failed: %s\n", strerror(errno));
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