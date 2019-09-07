/*
    Created by Maor Gershman, 25.8.2019
    ---
    This file contains important constants and includes.
*/

#pragma once

#include <string>
#include <array>

#ifdef __arm__
#define RASPBERRY_PI
#endif // __arm__

namespace SatelliteSoftware {
    constexpr std::array<uint8_t, 4> DefaultAddress = {10, 17, 110, 69};
    constexpr uint16_t DefaultPort = 550;
}