/*
    Created by Maor Gershman, 25.8.2019
    ---
    This file contains important constants and includes.
*/

#pragma once

#include <string>

#ifdef __arm__
#define RASPBERRY_PI
#endif // __arm__

namespace SatelliteSoftware {
    constexpr const char *Address = "10.17.110.69";
    constexpr int Port = 550;
}