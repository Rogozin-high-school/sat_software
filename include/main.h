/*
    Created by Maor Gershman, 25.8.2019
    ---
    This file contains important constants and includes.
*/

#pragma once

#include "server.h"
#include <string>
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <stdexcept>
#include <optional>

#include <arpa/inet.h>

#define IN_LAB false

namespace SatelliteSoftware {
    #ifdef RASPBERRY_PI
    constexpr bool isRaspberryPi = true;
    #else
    constexpr bool isRaspberryPi = false;
    #endif

    #if IN_LAB
    constexpr Server<Address<10, 17, 110, 134>, 550> server;
    #else
    constexpr Server<Address<84, 109, 40, 45>, 8888> server;
    #endif

    constexpr int maxPacketSize = 1024;

    using Timepoint = std::chrono::high_resolution_clock::time_point;
    using Byte = char;
    using Socket = int;
    using SocketAddress = sockaddr_in;
}