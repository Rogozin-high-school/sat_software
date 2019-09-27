/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will handle the communication with the ground station.
*/

#include "../include/client.h"
#include "../include/logger.h"
#include "../include/packets/packet_in.h"
#include "../include/packets/packet_out_send_mgm_values.h"
#include "../include/Torq/Torq.hpp"

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
        Packets::PacketIn packetIn(sock);
        while (connected) {
            auto input = packetIn.receive_packet<1>();
            if (input.has_value()) {
                std::array data = input.value();
                switch (packetIn.type) {
                case Packets::PacketIn::Type::UNKNOWN:
                    Logger::warn("Received unknown packet! ID = " + std::to_string(data[0]), LogPrefix::CLIENT);
                    break;
                case Packets::PacketIn::Type::KEEPALIVE: // Don't do anything.
                    break;
                case Packets::PacketIn::Type::REQUIRE_MGM_VALUES:
                    Packets::PacketOutSendMGMValues packetOut(sock, imu);
                    packetOut.send_packet();
                    break;
                case Packets::PacketIn::Type::TORQ_FIELD: // use torq
                    auto field_direction = packetIn.receive_packet<1>();
                    
                    // TODO: use the torq library to use the mgnetic field
                    break;
                }
            } else {
                Logger::severe("Lost connection with the ground station!", LogPrefix::CLIENT);
                connected = false;
            }
        }
    }

    void Client::cleanup() {
        if (sock != codeInvalidSocket) {
            close(sock);
        }
    }

    void Client::attempt_connection(bool& isConnected) {
        while (!isConnected) {
            // If connection has failed, reopen the socket and retry
            if (connect(sock, (sockaddr*)&sockAddr, sizeof(SocketAddress)) == codeNotConnected) {
                close(sock);
                create_socket();
            } else 
                isConnected = true;
        }
    }

    void Client::create_socket() {
        // Open the socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == codeInvalidSocket)
            throw std::runtime_error("Unable to open socket!");

        // Set the socket's address and port
        sockAddr.sin_family = AF_INET;
        sockAddr.sin_port = htons(port);
        if (inet_pton(AF_INET, address.c_str(), &sockAddr.sin_addr.s_addr) != codeAddressParseSucceeded)
            throw std::runtime_error("Unable to parse address!");

        // Set the socket's timeout
        timeval timeout = { 0, socketTimeoutMillis * 1000 };
        bool b1 = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeval)) == codeSetSocketOptFailed;
        bool b2 = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeval)) == codeSetSocketOptFailed;
        if (b1 || b2)
            throw std::runtime_error("Unable to set socket timeout!");
    }
}