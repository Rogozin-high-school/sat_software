#pragma once

#include <array>
#include <unordered_map>

enum class Axis : unsigned char {
    X, Y, Z
};

#ifdef RASPBERRY_PI // Real magnetorquer

#include <raspberry_pi/hbridge.hpp>

using namespace RaspberryPi;

namespace Modules {
    class Magnetorquer {
    public:
        void initialize();
        void set_torque_direction(Axis axis, HBridgeDirection direction);
        void reset_torque_directions();
        void cleanup();
    private:
        std::unordered_map<Axis, HBridge> HBridges;
    };
}

#else // Fake magnetorquer

using HBridgeDirection = char;

namespace Modules {
    class Magnetorquer {
    public:
        void initialize();
        void set_torque_direction(Axis axis, HBridgeDirection direction);
        void reset_torque_directions();
        void cleanup();
    private: 
        static constexpr HBridgeDirection NONE = 0;
        std::unordered_map<Axis, HBridgeDirection> HBridgesDirections { };
    };
}

#endif // RASPBERRY_PI