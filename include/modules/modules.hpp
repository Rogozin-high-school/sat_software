#pragma once

#include <modules/imu/imu.hpp>
#include <modules/magnetorquer/magnetorquer.hpp>

namespace Modules {
    void initialize(IMU& imu, Magnetorquer& magnetorquer);
}