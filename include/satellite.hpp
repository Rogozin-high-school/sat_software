#pragma once

#include <modules/modules.hpp>

class Satellite {
public:
    Satellite();
    ~Satellite();

    void initialize();
    void run();
    void cleanup();
private:
    Modules::IMU imu;
    Modules::Magnetorquer magnetorquer;
};