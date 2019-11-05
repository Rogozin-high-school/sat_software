#include <modules/magnetorquer/hbridge.hpp>

namespace Modules::SubModules {
    void HBridge::initialize(GPIO::Pin pin1, GPIO::Pin pin2) {
        directionPort1.initialize(pin1);
        directionPort2.initialize(pin2);
        
        directionPort1.export_gpio(); 
        directionPort2.export_gpio();

        directionPort1.set_direction(GPIO::Direction::OUT);
        directionPort2.set_direction(GPIO::Direction::OUT);
    }

    void HBridge::set_direction(HBridge::Direction direction) {
        switch (direction) {
            case HBridge::Direction::NONE: { // All gates are open
                directionPort1.set_value(GPIO::Value::OPEN);
                directionPort2.set_value(GPIO::Value::OPEN);
                break;
            } 
            case HBridge::Direction::FORWARD: { // All gates are closed, except for directionPort1
                directionPort1.set_value(GPIO::Value::OPEN);
                directionPort2.set_value(GPIO::Value::CLOSED);
                break;
            }
            case HBridge::Direction::BACKWARD: { // All gates are closed, except for directionPort2
                directionPort1.set_value(GPIO::Value::CLOSED);
                directionPort2.set_value(GPIO::Value::OPEN);
                break;
            }
        }
        _direction = direction;
    }

    void HBridge::cleanup() {
        directionPort1.unexport_gpio();
        directionPort2.unexport_gpio();
    }
}