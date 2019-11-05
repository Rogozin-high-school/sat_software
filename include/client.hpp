/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will handle the communication with the ground station.
*/

#pragma once

#include <arpa/inet.h>

#include <client_base.hpp>
#include <helper.hpp>

using SocketAddress = sockaddr_in;

class Client {
    static constexpr int socketTimeoutMillis       = 500;
public:
    Client();
    ~Client();

    void start_connection();
    void communicate(Modules::IMU& imu, Modules::Magnetorquer& magnetorquer);
    void cleanup();
private:
    std::string address;
    int port;

    SocketAddress sockAddr;
    Socket socketFD = -1;

    void create_socket();
    void attempt_connection(bool& isConnected);
};