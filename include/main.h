/*
    Created by Maor Gershman, 25.8.2019
    ---
    This file will contains important constants and includes.
*/

#pragma once

// AFAIK, __arm__ is only defined in Raspberry Pi.
#ifdef __arm__
#define RASPBERRY_PI // A much better name :)
#endif

namespace SatelliteSoftware {
    constexpr const char *Address = "10.17.110.69";
    constexpr int Port = 550;
}