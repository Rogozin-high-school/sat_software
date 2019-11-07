/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will handle the communication with the ground station.
*/

#include <client.hpp>
#include <logger.hpp>
#include <packets.hpp>
#include <properties.hpp>
#include <thread>
#include <chrono>

Client::Client() {
    address = Properties::get_string("ground_station_address");
    port = Properties::get_int("ground_station_port");
}

Client::~Client() {
    cleanup();
    Logger::verbose<LogPrefix::CLIENT>("Destroyed the client instance!");
}

inline Timepoint current_time() {
    return std::chrono::high_resolution_clock::now();
}

void Client::start_connection() {
    bool isConnected = false;

    Logger::info<LogPrefix::CLIENT>("Attempting to connect to the ground station!");
    Logger::debug<LogPrefix::CLIENT>("Ground station: " + address + ":" + std::to_string(port));
    create_socket();

    Timepoint whenStarted = current_time();
    std::thread connectionThread(&Client::attempt_connection, this, std::ref(isConnected));
    connectionThread.detach();

    Helper::draw_animation_with_dots(isConnected, "Connecting", std::chrono::milliseconds(200), 0, 5,
        [&](const std::string& text) {
            Logger::info<LogPrefix::CLIENT>(text);
        }
    );

    Timepoint whenFinished = current_time();
    std::string delayStr = Helper::time_period_to_string(whenStarted, whenFinished);
    Logger::info<LogPrefix::CLIENT>("Connected after " + delayStr + "!");
}

void Client::communicate(Modules::IMU& imu, Modules::Magnetorquer& magnetorquer) {
    using namespace Packets;
    
    while (true) {
        ReceivablePacket recvPacket = receive_packet(socketFD);
        
        if (is_error_packet(recvPacket)) {
            Logger::severe<LogPrefix::CLIENT>("Lost connection with the ground station!");
            break;
        }

        if (is_unknown_packet(recvPacket)) {
            Logger::verbose<LogPrefix::CLIENT>("Received an unknown packet!");
            continue;
        }

        ValidInPacket& validInPacket = std::get<ValidInPacket>(recvPacket);
        PacketId packetId = static_cast<PacketId>(validInPacket.index());

        switch (packetId) {
            case PacketId::KEEPALIVE: {
                send_packet(KeepAliveResponsePacket::instance, socketFD);
                break;
            }
            case PacketId::MGM: {
                send_packet(RequireMGMValuesResponsePacket(imu.read_magnetometer()), socketFD);
                break;
            }
            case PacketId::MAGNETORQUER: {
                UseMagnetorquerPacket packet = std::get<UseMagnetorquerPacket>(validInPacket);
                packet.start_torque(magnetorquer);
                send_packet(UseMagnetorquerResponsePacket::instance, socketFD);
                break;
            }
        }
    }
}

void Client::cleanup() {
    Logger::verbose<LogPrefix::CLIENT>("Cleaning up!");
    if (socketFD != -1) {
        close(socketFD);
    }
}

void Client::attempt_connection(bool& isConnected) {
    while (!isConnected) {
        // If connection has failed, reopen the socket and retry
        if (connect(socketFD, (sockaddr*)&sockAddr, sizeof(SocketAddress)) == -1) {
            close(socketFD);
            create_socket();
        } else {
            isConnected = true;
        }
    }
}

void Client::create_socket() {
    // Open the socket
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1) {
        throw std::runtime_error("Unable to open socket!");
    }

    // Set the socket's address and port
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, address.c_str(), &sockAddr.sin_addr.s_addr) != 1) {
        throw std::runtime_error("Unable to parse address!");
    }

    // Set the socket's timeout
    timeval timeout = { 0, socketTimeoutMillis * 1000 };
    bool b1 = setsockopt(socketFD, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeval)) == -1;
    bool b2 = setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeval)) == -1;
    if (b1 || b2) {
        throw std::runtime_error("Unable to set socket timeout!");
    }
}
