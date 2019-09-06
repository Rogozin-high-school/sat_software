/*
    Created by Maor Gershman, 25.8.2019
    ---
    Note: Networking should be done on a seperate thread!
*/

#include "../include/logger.h"
#include "../include/client.h"
#include <unistd.h>
#include <thread>
#include <chrono>

namespace Satellite {
    Client::Client(std::string address, int port) : address(address), port(port) {
        create_socket();
        if (failure()) {
            return;
        }
        attempt_connection();
    }

    Client::~Client() {
        if (socketHandle != -1) {
            close(socketHandle);
            Logger::debug("Closed the socket!", Logger::LogPrefix::CLIENT);
        }
    }

    void Client::create_socket() {
        Logger::debug("Creating the socket...", Logger::LogPrefix::CLIENT);

        // Open the socket
        socketHandle = socket(AF_INET, SOCK_STREAM, 0);
        lastOperationSuccessful = socketHandle != -1;
        if (success()) {
            Logger::debug("Opened the socket!", Logger::LogPrefix::CLIENT);
        } else {
            return;
        }

        // Set the socket's address and port
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(port);
        lastOperationSuccessful = inet_pton(AF_INET, address.c_str(), &socketAddress.sin_addr.s_addr) == 1;
        if (failure()) {
            return;
        }
        
        // Set the socket's timeout
        timeval timeout = { SocketTimeoutSeconds, 0 };
        lastOperationSuccessful = setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) == 0;
    }

    void Client::attempt_connection() {
        Logger::info("Attempting connection to " + address + ":" + std::to_string(port) + "...", Logger::LogPrefix::CLIENT);

        // Attempt to connect to the server (on a new thread).
        int connectionStatus = -1;
        std::thread connectionThread([&] {
            connectionStatus = connect(socketHandle, (sockaddr*)&socketAddress, sizeof(socketAddress));
        });
        connectionThread.detach();

        // Meanwhile, count down how much time remains until the connection fails.
        for (int t = SocketTimeoutSeconds; connectionStatus == -1 && t > 0; t--) {
            Logger::debug(std::to_string(t) + " seconds remaining to the timeout...", Logger::LogPrefix::CLIENT);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        lastOperationSuccessful = connectionStatus == 0;
    }

    bool Client::success() const {
        return lastOperationSuccessful;
    }

    bool Client::failure() const {
        return !lastOperationSuccessful;
    }
}