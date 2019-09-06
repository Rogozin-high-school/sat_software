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
#include <chrono>
#include <string>

namespace SatelliteSoftware {
    class Client {
    private:
        std::string address;
        int port;

        sockaddr_in socketAddress;
        int socketHandle = -1;
        
        bool sockFailed;

        bool create_socket() {
            Logger::debug("Creating the socket...", Logger::Prefix::CLIENT);

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

            Logger::debug("Opened the socket at " + address + ":" + std::to_string(port) + "!", Logger::Prefix::CLIENT);
            return true;
        }

        void start_connection() {
            Logger::info("Attempting to connect to the ground station!", Logger::Prefix::CLIENT);

            // Attempt to connect on a new thread.
            int status = -1;
            std::thread connectionThread([&] {
                status = connect(socketHandle, (sockaddr*)&socketAddress, sizeof(socketAddress));
            });
            connectionThread.detach();

            bool increasing = true;
            int dots = 0;
            while (status != 0) {
                std::string str = "Connecting";
                int j = 0;
                for (; j < dots; j++) {
                    str += ".";
                }
                for (; j < 5; j++) {
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
            std::cout << std::endl;

            Logger::info("Connected!", Logger::Prefix::CLIENT);
        }
    public:
        const bool& socketFailed = sockFailed;

        Client(std::string address = Address, int port = Port) 
            : address(address), port(port) 
        {
            if (!create_socket()) {
                sockFailed = true;
                return;
            }
            start_connection();
        }

        ~Client() {
            if (socketHandle != -1) {
                close(socketHandle);
                Logger::debug("Closed the socket!", Logger::Prefix::CLIENT);
            }
        }
    };
}