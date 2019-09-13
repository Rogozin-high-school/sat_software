/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will handle the communication with the ground station.
*/

#include "../include/client.h"
#include "../include/logger.h"
#include <unistd.h>
#include <cstring>

namespace SatelliteSoftware {
    Client::Client() : 
        address(Helper::address_to_string(Address)), 
        port(Port),
        socketHandle(CodeInvalidSocket)
    {}

    Client::~Client() {
        cleanup();
    }

    void Client::start_connection() {
        bool isConnected = false;

        Logger::info("Attempting to connect to the ground station!", LogPrefix::CLIENT);
        Logger::debug("Ground station: " + address + ":" + std::to_string(port), LogPrefix::CLIENT);
        create_socket();
        Timepoint whenStarted = Helper::current_time();

        std::thread connectionThread(&Client::attempt_connection, this, std::ref(isConnected));
        connectionThread.detach();

        Helper::draw_animation_with_dots(isConnected, "Connecting", std::chrono::milliseconds(200), 0, 5,
            [&](const std::string& text) {
                Logger::info(text, LogPrefix::CLIENT);
            }
        );

        Timepoint whenFinished = Helper::current_time();
        std::string delayStr = Helper::time_period_to_string(whenStarted, whenFinished);
        Logger::info("Connected after " + delayStr + "!", LogPrefix::CLIENT);
    }

    void Client::communicate(IMU& imu) {
        char serverResponse;
        int status;
        while (true) {
            status = read(socketHandle, &serverResponse, 1);
            if (status <= 0) {
                Logger::severe("Lost connection with the ground station!", LogPrefix::CLIENT);
                return;
            }
            Logger::debug("Server send code " + std::to_string((int)serverResponse) + "!");
            if (serverResponse == 0) {
                // Don't do anything
                continue;
            }
            if (serverResponse == 1) {
                // Send MGM values
                std::array<float, 3> mgmValues = imu.read_magnetometer();
                Logger::debug(
                    "Read MGM values: (" + std::to_string(mgmValues[0]) +
                    ", " + std::to_string(mgmValues[1]) +
                    ", " + std::to_string(mgmValues[2]) + ")",
                    LogPrefix::IMU);
                char buffer[13];
                buffer[0] = 1;
                memcpy(buffer + 1, &mgmValues[0], sizeof(float));
                memcpy(buffer + 5, &mgmValues[1], sizeof(float));
                memcpy(buffer + 9, &mgmValues[2], sizeof(float));
                send(socketHandle, buffer, sizeof(buffer), 0);
            }
        }
    }

    void Client::cleanup() {
        if (socketHandle != CodeInvalidSocket) {
            close(socketHandle);
        }
    }

    void Client::attempt_connection(bool& isConnected) {
        while (!isConnected) {
            // If connection has failed, reopen the socket and retry
            if (connect(socketHandle, (sockaddr*)&socketAddress, sizeof(socketAddress)) == CodeNotConnected) {
                close(socketHandle);
                create_socket();
            } else 
                isConnected = true;
        }
    }

    void Client::create_socket() {
        // Open the socket
        socketHandle = socket(AF_INET, SOCK_STREAM, 0);
        if (socketHandle == CodeInvalidSocket)
            throw std::runtime_error("Unable to open socket!");

        // Set the socket's address and port
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(port);
        if (inet_pton(AF_INET, address.c_str(), &socketAddress.sin_addr.s_addr) != CodeAddressParseSucceeded)
            throw std::runtime_error("Unable to parse address!");

        // Set the socket's timeout
        timeval timeout = { 0, SocketTimeoutMillis * 1000 };
        bool b1 = setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) == CodeSetSocketOptFailed;
        bool b2 = setsockopt(socketHandle, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == CodeSetSocketOptFailed;
        if (b1 || b2)
            throw std::runtime_error("Unable to set socket timeout!");
    }
}