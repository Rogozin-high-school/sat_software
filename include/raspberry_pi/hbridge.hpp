#ifdef RASPBERRY_PI

#pragma once

#include <raspberry_pi/gpio.hpp>

namespace RaspberryPi {
    enum class HBridgeDirection : char {
        NONE = 0,
        FORWARD = 1,
        BACKWARD = -1
    };

    class HBridge {
    public:
        const HBridgeDirection& direction = _direction;

        void initialize(PinNumber pin1, PinNumber pin2);
        void cleanup();
        void set_direction(HBridgeDirection direction);
    private:
        GPIO directionPort1, directionPort2;
        HBridgeDirection _direction = HBridgeDirection::NONE;
    };
}

#endif // RASPBERRY_PI