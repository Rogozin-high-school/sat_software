#include <modules/magnetorquer/magnetorquer.hpp>

namespace Modules {
    void Magnetorquer::initialize() {
        HBridges[Axis::X].initialize(SubModules::GPIO::Pin(20), SubModules::GPIO::Pin(26));
        HBridges[Axis::Y].initialize(SubModules::GPIO::Pin(16), SubModules::GPIO::Pin(19));
        HBridges[Axis::Z].initialize(SubModules::GPIO::Pin(23), SubModules::GPIO::Pin(22));
    }

    void Magnetorquer::set_torque_direction(Axis axis, SubModules::HBridge::Direction direction) {
        HBridges[axis].set_direction(direction);
    }

    void Magnetorquer::reset_torque_directions() {
        set_torque_direction(Axis::X, SubModules::HBridge::Direction::NONE);
        set_torque_direction(Axis::Y, SubModules::HBridge::Direction::NONE);
        set_torque_direction(Axis::Z, SubModules::HBridge::Direction::NONE);
    }

    void Magnetorquer::cleanup() {
        HBridges[Axis::X].cleanup();
        HBridges[Axis::Y].cleanup();
        HBridges[Axis::Z].cleanup();
    }
}