/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will handle the communication with the ground station.
*/

#include "../include/client.h"
#include "../include/logger.h"
#include "../include/packets/packet_in.h"
#include "../include/packets/packet_out_send_mgm_values.h"

namespace SatelliteSoftware {
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
        bool connected = true;
        Packets::PacketIn packetIn(socketHandle);
        while (connected) {
            try {
                std::array input = packetIn.receive_packet<1>();
                switch (packetIn.type) {
                case Packets::PacketIn::Type::UNKNOWN:
                    Logger::warn("Received unknown packet! ID = " + std::to_string(input[0]), LogPrefix::CLIENT);
                    break;
                case Packets::PacketIn::Type::KEEPALIVE: // Don't do anything.
                    break;
                case Packets::PacketIn::Type::REQUIRE_MGM_VALUES:
                    Packets::PacketOutSendMGMValues packetOut(socketHandle, imu);
                    packetOut.send_packet();
                    break;
                }
            } catch (const std::exception& ex) {
                Logger::severe("Lost connection with the ground station!", LogPrefix::CLIENT);
                connected = false;
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