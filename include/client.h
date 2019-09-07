/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will handle the communication with the ground station.
*/

#pragma once
#include "main.h"
#include "logger.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

namespace SatelliteSoftware {
    class Client {
    private:
        static constexpr int ConnectionAttemptSeconds = 5;
        static constexpr int ConnectionAttemptCooldownSeconds = 3;

        std::string address;
        int port;

        sockaddr_in socketAddress;
        int socketHandle = -1;
        
        bool sockFailed;

        bool create_socket() {
            // Open the socket
            socketHandle = socket(AF_INET, SOCK_STREAM, 0);
            if (socketHandle == -1) {
                Logger::error("Unable to open socket!", Logger::Prefix::CLIENT);
                return false;
            }

            // Set the socket's address and port
            socketAddress.sin_family = AF_INET;
            socketAddress.sin_port = htons(port);
            if (inet_pton(AF_INET, address.c_str(), &socketAddress.sin_addr.s_addr) != 1) {
                Logger::error("Unable to parse address!", Logger::Prefix::CLIENT);
                return false;
            }

            // Set the socket's timeout
            timeval timeout = { ConnectionAttemptSeconds, 0 };
            if (setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) != 0) {
                Logger::error("Unable to set socket timeout!", Logger::Prefix::CLIENT);
                return false;
            }

            return true;
        }

        // TODO: Document or split this code to smaller functions.

        bool start_connection() {
            Logger::info("Attempting to connect to the ground station!", Logger::Prefix::CLIENT);
            Logger::debug("Ground station: " + address + ":" + std::to_string(port), Logger::Prefix::CLIENT);
            auto whenStarted = std::chrono::high_resolution_clock::now();

            // If an initial socket creation fails, then the address/port is probably broken!
            if (!create_socket()) {
                return false;
            }

            // Attempt to connect on a new thread.
            bool connecting = true;   
            int status = -1;
            std::thread connectionThread([&] {
                while (status != 0) {
                    // Attempt to connect until cooldown hits.
                    connecting = true;
                    status = connect(socketHandle, (sockaddr*)&socketAddress, sizeof(socketAddress));
                    // If connection has failed, cooldown.
                    if (status != 0) {
                        connecting = false;
                        close(socketHandle);
                        // Sleep and open a new socket.
                        std::this_thread::sleep_for(std::chrono::seconds(ConnectionAttemptCooldownSeconds));
                        create_socket();
                    }
                }
            });
            connectionThread.detach();

            bool increasing = true;
            int dots = 0;
            while (status != 0) {
                std::string str = connecting ? "Connecting" : "Cooling down";
                int i = 0;
                for (; i < dots; i++) {
                    str += ".";
                }
                for (; i < 5; i++) {
                    str += " ";
                }
                Logger::info(str, Logger::Prefix::CLIENT);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                // Move to the previous line
                std::cout << "\x1B[1F" << std::flush;
                
                if (increasing) {
                    if (++dots == 5) {
                        increasing = false;
                    }
                } else {
                    if (--dots == 0) {
                        increasing = true;
                    }
                }
            }

            auto whenFinished = std::chrono::high_resolution_clock::now();
            std::string delayStr = Helper::time_period_to_string(whenStarted, whenFinished);
            Logger::info("Connected after " + delayStr + "!", Logger::Prefix::CLIENT);
            return true;
        }
    public:
        const bool& socketFailed = sockFailed;

        Client(std::string address = Address, int port = Port) 
            : address(address), port(port) 
        {
            if (!start_connection()) {
                sockFailed = true;
                return;
            }
        }

        ~Client() {
            if (socketHandle != -1) {
                close(socketHandle);
            }
        }
    };
}