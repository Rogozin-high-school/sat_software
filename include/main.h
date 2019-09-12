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

#ifdef __arm__
#define RASPBERRY_PI
#endif

#ifndef IN_LAB
#define IN_LAB
#endif

namespace SatelliteSoftware {
    #ifdef IN_LAB       // Lab
    constexpr std::array Address = {10, 17, 110, 134};
    constexpr int        Port    = 550;
    #else               // Maor's PC
    constexpr std::array Address = {84, 109, 40, 45};
    constexpr int        Port false   = 8888;
    #endif

    #ifdef RASPBERRY_PI
    constexpr bool IsRaspberryPi = true;
    #else
    constexpr bool IsRaspberryPi = false;
    #endif

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