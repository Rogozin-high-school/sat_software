#ifdef RASPBERRY_PI

#include <raspberry_pi/hbridge.hpp>

namespace RaspberryPi {
    void HBridge::initialize(PinNumber pin1, PinNumber pin2) {
        directionPort1.initialize(pin1);
        directionPort2.initialize(pin2);
        
        // export GPIO pins
        directionPort1.export_gpio(); 
        directionPort2.export_gpio();

        // set GPIO pin direction to output
        directionPort1.set_direction(GPIODirection::OUT);
        directionPort2.set_direction(GPIODirection::OUT);
    }

    void HBridge::cleanup() {
        directionPort1.unexport_gpio();
        directionPort2.unexport_gpio();
    }

    void HBridge::set_direction(HBridgeDirection direction) {
        switch (direction) {
            case HBridgeDirection::NONE: { // all gates are open
                directionPort1.set_value(0);
                directionPort2.set_value(0);
                break;
            } 
            case HBridgeDirection::FORWARD: { // all gates are closed except for directionPort1
                directionPort1.set_value(0);
                directionPort2.set_value(1);
                break;
            }
            case HBridgeDirection::BACKWARD: { // all gates are closed except for directionPort2
                directionPort1.set_value(1);
                directionPort2.set_value(0);
                break;
            }
        }
        this->_direction = direction;
    }
}

#endif // RASPBERRY_PI