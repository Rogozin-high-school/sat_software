#pragma once

#include <modules/magnetorquer/gpio.hpp>

namespace Modules::SubModules {
    class HBridge {
    public:
        enum class Direction {
            NONE     = 0,
            FORWARD  = 1,
            BACKWARD = -1
        };

        const HBridge::Direction& direction = _direction;

        void initialize(GPIO::Pin pin1, GPIO::Pin pin2);
        void set_direction(HBridge::Direction direction);
        void cleanup();
    private:
        GPIO directionPort1;
        GPIO directionPort2;

        HBridge::Direction _direction = HBridge::Direction::NONE;
    };
}