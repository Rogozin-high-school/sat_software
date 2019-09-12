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
    constexpr int SocketTimeoutMillis = 500;
    constexpr int CodeInvalidSocket = -1;
    constexpr int CodeNotConnected = -1;
    constexpr int CodeAddressParseSucceeded = 1;
    constexpr int CodeSetSocketOptFailed = -1;
    
    class Client {
    private:
        std::string address;
        int port;

        sockaddr_in socketAddress;
        int socketHandle;

        bool create_socket();
    public:
        Client();
        ~Client();

        bool start_connection();
        void communicate(IMU& imu);
    };
}