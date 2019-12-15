#include <client.hpp>
#include <logger.hpp>
#include <properties.hpp>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>

//////////////////////////////////

int clientTimeoutMicros;

int socketFD;
sockaddr_in socketAddress;

int port;
char address[16];

enum class Intent : uint8_t
{
    None = 0x00,
    Terminate = 0xff
};

Intent intent = Intent::None;

//////////////////////////////////

inline void start_connection() noexcept;
inline void communicate() noexcept;
inline void cleanup() noexcept;
inline bool create_socket() noexcept;

//////////////////////////////////

bool Client::initialize() noexcept
{
    // ground_station_address
    strcpy(address, Properties::get_string("ground_station_address").c_str());
    // ground_station_port
    port = Properties::get_int("ground_station_port");
    // client_timeout_micros
    clientTimeoutMicros = Properties::get_int("client_timeout_micros");
    return true;
}

void Client::run() noexcept
{
    while (intent != Intent::Terminate)
    {
        start_connection();
        communicate();
        cleanup();
    }
}

void start_connection() noexcept
{
    while (true)
    {
        log("Attempting to connect to %s:%d!\n", address, port);

        // Attempt to create the socket file descriptor
        if (!create_socket())
        {
            log("client.start_connection().create_socket() has failed!\n");
            continue;
        }

        // Attempt to connect the socket file descriptor to the socket address
        if (connect(socketFD, (sockaddr *)&socketAddress, sizeof(socketAddress)))
        {
            log("client.start_connection().connect() has failed: %s\n", strerror(errno));
            cleanup();
            usleep(clientTimeoutMicros);
            continue;
        }
        else
        { // If succeeded, break the loop.
            log("Connected to the ground station!\n");
            break;
        }
    }
}

void communicate() noexcept
{
    ssize_t bytes;
    uint8_t buffer[1024];

    log("Waiting for an initial packet...\n");

    while (intent != Intent::Terminate)
    {
        memset(buffer, 0, sizeof(buffer));

        bytes = read(socketFD, buffer, sizeof(buffer));
        if (bytes == -1)
        {
            log("client.communicate().read() has failed: %s\n", strerror(errno));
        }
        else if (bytes == 0)
        {
            log("client has received EOF!\n");
        }
        else
        {
            uint8_t packetId = buffer[0];
            log("Received packet with ID = %d\n", packetId);
            switch (packetId)
            {
            case uint8_t(Intent::Terminate):
                log("Received terminate packet!\n");
                intent = Intent::Terminate;
            default:
                break;
            }
        }
    }
}

void cleanup() noexcept
{
    if (close(socketFD))
    {
        log("client.cleanup().close() has failed: %s\n", strerror(errno));
    }
}

bool create_socket() noexcept
{
    { // Create the socket file descriptor.
        socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFD == -1)
        {
            log("client.create_socket().socket() has failed: %s\n", strerror(errno));
            return false;
        }
    }

    { // Initialize the server address.
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(port);
        if (inet_pton(AF_INET, address, &socketAddress.sin_addr.s_addr) != 1)
        {
            log("client.create_socket().inet_pton() has failed: %s\n", strerror(errno));
            return false;
        }
    }

    if (clientTimeoutMicros > 0)
    { // Set the socket timeout
        const int timeoutSeconds = clientTimeoutMicros / 1000000;
        const int timeoutMicroseconds = clientTimeoutMicros % 1000000;

        const timeval timeout = {timeoutSeconds, timeoutMicroseconds};

        if (setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO | SO_SNDTIMEO, &timeout, sizeof(timeval)))
        {
            log("client.create_socket().setsockopt() has failed: %s\n", strerror(errno));
            return false;
        }
    }

    return true;
}