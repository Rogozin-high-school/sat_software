/*
    Created by Yanir Harel, 28.9.2019
    ---------------------------------
    This module is used to set the power flow direction of the electric current.
*/

#pragma once

#include "Gpio.hpp"
#include <chrono>
#include <exception>
#include <thread>

using std::string;

class hBridge {
public:
    hBridge(string[]);
    ~hBridge(void);
    void setDirection(int);
private:
    GPIOClass* ports[2]; // [0] = directioPort1, [1] = directionPort2
};