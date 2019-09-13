/*
    Created by Maor Gershman, 25.8.2019
    ---
    This file contains important constants and includes.
*/

#pragma once

#include <string>
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <stdexcept>

namespace SatelliteSoftware {
    #ifdef RASPBERRY_PI
    constexpr bool IsRaspberryPi = true;
    #else
    constexpr bool IsRaspberryPi = false;
    #endif

    constexpr bool InLab = false;

    constexpr auto Address = InLab ?
        std::array {10, 17, 110, 134} :
        std::array {84, 109, 40, 45};
    constexpr int  Port    = InLab ? 
        550 : 
        8888;

    using Timepoint = std::chrono::high_resolution_clock::time_point;

    static_assert(
        Address[0] > 0 && Address[0] < 0xFF &&
        Address[1] > 0 && Address[1] < 0xFF &&
        Address[2] > 0 && Address[2] < 0xFF &&
        Address[3] > 0 && Address[3] < 0xFF,
        "Bad address!"
    );

    static_assert(Port > 0 && Port < 0xFFFF, "Bad port!");
}