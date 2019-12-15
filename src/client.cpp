#include <client.hpp>
#include <logger.hpp>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>

//////////////////////////////////

int socketTimeoutMicros;

int socketFD;
sockaddr_in socketAddress;

int port;
char address[16];

//////////////////////////////////

inline void start_connection() noexcept;
inline bool communicate() noexcept;
inline void cleanup() noexcept;

inline bool create_socket() noexcept;
inline void analyze(const char *const buffer, ssize_t size) noexcept;

//////////////////////////////////

bool Client::initialize() noexcept
{
    // TODO: Load from the properties

    // Meanwhile:
    socketTimeoutMicros = 500 * 1000;
    port = 8888;
    strcpy(address, "127.0.0.1");

    return true;
}

bool Client::run() noexcept
{
    bool intentionalShutdown = false;
    while (!intentionalShutdown)
    {
        start_connection();

        if (!communicate())
        { // If returned false, recover.
            log << "client.communicate() has failed!\n";
        }
        else
        { // If returned true, it means that the shutdown was intentional!
            intentionalShutdown = true;
        }

        cleanup();
    }
    return true;
}

void start_connection() noexcept
{
    while (true)
    {
        log << "Attempting to connect to " << address << ":" << port << "!\n";

        // Attempt to create the socket file descriptor
        if (!create_socket())
        {
            log << "client.start_connection().create_socket() has failed!\n";
            continue;
        }

        // Attempt to connect the socket file descriptor to the socket address
        if (connect(socketFD, (sockaddr *)&socketAddress, sizeof(socketAddress)))
        {
            log << "client.start_connection().connect() has failed: " << strerror(errno) << "\n";
            cleanup();
            usleep(socketTimeoutMicros);
            continue;
        }
        else
        { // If succeeded, break the loop.
            log << "Connected to the ground station!\n";
            break;
        }
    }
}

bool communicate() noexcept
{
    ssize_t bytes;
    char buffer[1024]{};

    log << "Waiting for initial packet...\n";

    while (true)
    {
        bytes = read(socketFD, buffer, sizeof(buffer));
        if (bytes == -1)
        {
            log << "client.communicate().read() has failed" << strerror(errno) << "\n";
        }
        else if (bytes == 0)
        {
            log << "client has received EOF!\n";
        }
        else
        {
            analyze(buffer, bytes);
        }
    }

    return true;
}

void cleanup() noexcept
{
    if (close(socketFD))
    {
        log << "close() has failed: " << strerror(errno) << "\n";
    }
    else
    {
        log << "Client has been cleaned up!\n";
    }
}

bool create_socket() noexcept
{
    { // Create the socket file descriptor.
        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD == -1)
        {
            log << "client.create_socket().socket() has failed: " << strerror(errno) << "\n";
            return false;
        }
    }

    { // Initialize the server address.
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(port);
        if (inet_pton(AF_INET, address, &socketAddress.sin_addr.s_addr) != 1)
        {
            log << "client.create_socket().inet_pton() has failed: " << strerror(errno) << "\n";
            return false;
        }
    }

    if (socketTimeoutMicros > 0)
    { // Set the socket timeout
        const int timeoutSeconds = socketTimeoutMicros / 1000000;
        const int timeoutMicroseconds = socketTimeoutMicros % 1000000;

        const timeval timeout = {timeoutSeconds, timeoutMicroseconds};

        if (setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO | SO_SNDTIMEO, &timeout, sizeof(timeval)))
        {
            log << "client.create_socket().setsockopt() has failed: " << strerror(errno) << "\n";
            return false;
        }
    }

    return true;
}

void analyze(const char *const buffer, ssize_t size) noexcept
{
    char packetId = buffer[0];
    log << "Received packet with ID = " << packetId << "\n";
    switch (packetId)
    {
    default:
        break;
    }
}