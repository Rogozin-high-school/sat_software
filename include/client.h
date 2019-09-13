/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will handle the communication with the ground station.
*/

#pragma once

#include "main.h"
#include "imu.h"
#include <arpa/inet.h>

namespace SatelliteSoftware {
    constexpr int SocketTimeoutMillis       = 500;
    constexpr int CodeInvalidSocket         = -1;
    constexpr int CodeNotConnected          = -1;
    constexpr int CodeAddressParseSucceeded = 1;
    constexpr int CodeSetSocketOptFailed    = -1;
    
    class Client {
    public:
        Client();
        ~Client();

        void start_connection();
        void communicate(IMU& imu);
        void cleanup();
    private:
        const std::string address;
        const int port;

        sockaddr_in socketAddress;
        int socketHandle;

        void create_socket();
        void attempt_connection(bool& isConnected);
    };
}