/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will handle the communication with the ground station.
*/

#pragma once

#include <arpa/inet.h>

#include <client_base.hpp>
#include <helper.hpp>

#include <modules/imu.hpp>
#include <modules/magnetorquer.hpp>

using SocketAddress = sockaddr_in;

class Client {
    static constexpr int socketTimeoutMillis       = 500;

    static constexpr int codeInvalidSocket         = -1;
    static constexpr int codeNotConnected          = -1;
    static constexpr int codeAddressParseSucceeded = 1;
    static constexpr int codeSetSocketOptFailed    = -1;
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
    Socket sock = codeInvalidSocket;

    void create_socket();
    void attempt_connection(bool& isConnected);
};