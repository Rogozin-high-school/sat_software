/*
    Created by Maor Gershman, 25.8.2019
*/

#include "../include/logger.h"
#include "../include/client.h"

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
            Logger::log("Closed the socket!");
        }
    }

    void Client::create_socket() {
        Logger::log("Creating the socket...");

        // Open the socket
        socketHandle = socket(AF_INET, SOCK_STREAM, 0);
        lastOperationSuccessful = socketHandle != -1;
        if (success()) {
            Logger::log("Opened the socket!");
        } else {
            return;
        }

        // Set the socket's address and port
        socketStruct.sin_family = AF_INET;
        socketStruct.sin_port = htons(port);
        lastOperationSuccessful = 1 == inet_pton(AF_INET, address.c_str(), &socketStruct.sin_addr.s_addr);
        if (failure()) {
            return;
        }
        
        // Set the socket's timeout
        timeval timeout = { SocketTimeoutSeconds, 0 };
        lastOperationSuccessful = 0 == setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    }

    void Client::attempt_connection() {
        Logger::log("Attempting connection to " + address + ":" + std::to_string(port) + "...");

        // Attempt to connect to the server (on a new thread).
        int connectionStatus = -1;
        std::thread connectionThread([&] {
            connectionStatus = connect(socketHandle, (sockaddr*)&socketStruct, sizeof(socketStruct));
        });
        connectionThread.detach();

        // Meanwhile, count down how much time remains until the connection fails.
        int timeRemaining = SocketTimeoutSeconds;
        while (connectionStatus == -1 && timeRemaining > 0) {
            Logger::log(std::to_string(timeRemaining--) + " seconds remaining...");
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