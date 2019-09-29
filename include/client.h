/*
    Created by Maor Gershman, 25.8.2019
    Updated and Upgraded by Yanir Harel, 28.9.2019
    ---
    This class will handle the communication with the ground station.
*/

#pragma once

#include "main.h"
#include "imu.h"
#include "helper.h"
#include <chrono>
#include <thread>
#include "Torq/Torq.hpp"

namespace SatelliteSoftware {
    constexpr int socketTimeoutMillis       = 500;
    constexpr int codeInvalidSocket         = -1;
    constexpr int codeNotConnected          = -1;
    constexpr int codeAddressParseSucceeded = 1;
    constexpr int codeSetSocketOptFailed    = -1;
    
    class Client {
    public:
        ~Client();

        void start_connection();
        void communicate(IMU& imu, Torquer& torq);
        void cleanup();
    private:
        const std::string address = server.address.to_string();
        const int port = server.port;

        SocketAddress sockAddr;
        Socket sock = codeInvalidSocket;

        void create_socket();
        void attempt_connection(bool& isConnected);
    };
}