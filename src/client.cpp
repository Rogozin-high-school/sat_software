/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will handle the communication with the ground station.
*/

#include "../include/client.h"
#include "../include/logger.h"
#include <unistd.h>

namespace SatelliteSoftware {
    Client::Client() : 
        address(Helper::address_to_string(Address)), 
        port(Port), 
        socketHandle(CodeInvalidSocket), 
        socketFailed(propSocketFailed) 
    {
        if (!start_connection()) {
            propSocketFailed = true;
        }
    }

    Client::~Client() {
        if (socketHandle != CodeInvalidSocket) {
            close(socketHandle);
        }
    }

    bool Client::start_connection() {
        Logger::info("Attempting to connect to the ground station!", LogPrefix::CLIENT);
        Logger::debug("Ground station: " + address + ":" + std::to_string(port), LogPrefix::CLIENT);
        if (!create_socket())
            return false;
        Timepoint whenStarted = Helper::current_time();

        // Attempt to connect on a new thread.
        bool notConnected = true;
        std::thread connectionThread([&] {
            while (notConnected) {
                // If connection has failed, reopen the socket and retry
                if (connect(socketHandle, (sockaddr*)&socketAddress, sizeof(socketAddress)) == CodeNotConnected) {
                    close(socketHandle);
                    create_socket();
                } else {
                    notConnected = false;
                }
            }
        });
        connectionThread.detach();

        Helper::draw_animation_with_dots(notConnected, "Connecting", std::chrono::milliseconds(200), 0, 5,
            [&](const std::string& text) {
                Logger::info(text, LogPrefix::CLIENT);
            }
        );

        Timepoint whenFinished = Helper::current_time();
        std::string delayStr = Helper::time_period_to_string(whenStarted, whenFinished);
        Logger::info("Connected after " + delayStr + "!", LogPrefix::CLIENT);
        return true;
    }

    bool Client::create_socket() {
        // Open the socket
        socketHandle = socket(AF_INET, SOCK_STREAM, 0);
        if (socketHandle == CodeInvalidSocket) {
            Logger::error("Unable to open socket!", LogPrefix::CLIENT);
            return false;
        }

        // Set the socket's address and port
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(port);
        if (inet_pton(AF_INET, address.c_str(), &socketAddress.sin_addr.s_addr) != CodeAddressParseSucceeded) {
            Logger::error("Unable to parse address!", LogPrefix::CLIENT);
            return false;
        }

        // Set the socket's timeout
        timeval timeout = { ConnectionAttemptSeconds, 0 };
        if (setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) == CodeSetSocketOptFailed) {
            Logger::error("Unable to set socket timeout!", LogPrefix::CLIENT);
            return false;
        }

        return true;
    }
}