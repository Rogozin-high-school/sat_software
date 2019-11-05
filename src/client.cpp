/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will handle the communication with the ground station.
*/

#include <client.hpp>
#include <logger.hpp>
#include <packets/packet_in.hpp>
#include <packets/packet_out_send_mgm_values.hpp>
#include <thread>
#include <chrono>
#include <fstream>

Client::Client() {
    // Load server address & port from a file
    constexpr auto serverInfoFilePath = "server";
    std::string strAddress, strPort;

    std::ifstream file(serverInfoFilePath);
    std::getline(file, strAddress);
    std::getline(file, strPort);

    this->address = strAddress;
    this->port = stoi(strPort);

    file.close();
}

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

    Logger::info("Connecting...", LogPrefix::CLIENT);

    // Helper::draw_animation_with_dots(isConnected, "Connecting", std::chrono::milliseconds(200), 0, 5,
    //     [&](const std::string& text) {
    //         Logger::info(text, LogPrefix::CLIENT);
    //     }
    // );

    Timepoint whenFinished = Helper::current_time();
    std::string delayStr = Helper::time_period_to_string(whenStarted, whenFinished);
    Logger::info("Connected after " + delayStr + "!", LogPrefix::CLIENT);
}

void Client::communicate(Modules::IMU& imu, Modules::Magnetorquer& magnetorquer) {
    bool connected = true;
    Packets::PacketIn packetIn(socketFD);
    while (connected) {
        auto input = packetIn.receive_packet<1>();
        if (input.has_value()) {
            std::array data = input.value();
            switch (packetIn.type) {
                case Packets::PacketIn::Type::UNKNOWN: {
                    Logger::warn("Received unknown packet! ID = " + std::to_string(data[0]), LogPrefix::CLIENT);
                    break;
                }
                case Packets::PacketIn::Type::KEEPALIVE: { // Don't do anything.
                    break;
                }
                case Packets::PacketIn::Type::REQUIRE_MGM_VALUES: {
                    Packets::PacketOutSendMGMValues packetOut(socketFD, imu);
                    packetOut.send_packet();
                    break;
                }
                case Packets::PacketIn::Type::USE_TORQUE: {
                    // Logger::info("Starting Torq!", LogPrefix::CLIENT);
                    // auto fd = packetIn.receive_packet<3>();
                    // std::array fds = fd.value();
                    // if (torq.directions[0] != fds[0]) {
                    //     torq.set_dir_x(fds[0] == 2 ? -1 : fds[0]);
                    // }
                    // if (torq.directions[0] != 0) {
                    //     sleep_for(seconds(2));
                    //     torq.set_dir_x(0);
                    // }
                    // Logger::info("Stopping torq!", LogPrefix::CLIENT);
                    // Packets::PacketOut<1> pout(socketFD);
                    // pout.send_packet();
                    // TODO: fix this
                    break;
                }
            }
        } else {
            Logger::severe("Lost connection with the ground station!", LogPrefix::CLIENT);
            connected = false;
        }
    }
}

void Client::cleanup() {
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
