#include <modules/magnetorquer.hpp>

#ifdef RASPBERRY_PI // real magnetorquer

namespace Modules {
    void Magnetorquer::initialize() {
        HBridges[Axis::X].initialize(20, 26);
        HBridges[Axis::Y].initialize(16, 19);
        HBridges[Axis::Z].initialize(23, 22);
    }

    void Magnetorquer::set_torque_direction(Axis axis, HBridgeDirection direction) {
        HBridges[axis].set_direction(direction);
    }

    void Magnetorquer::reset_torque_directions() {
        set_torque_direction(Axis::X, HBridgeDirection::NONE);
        set_torque_direction(Axis::Y, HBridgeDirection::NONE);
        set_torque_direction(Axis::Z, HBridgeDirection::NONE);
    }

    void Magnetorquer::cleanup() {
        HBridges[Axis::X].cleanup();
        HBridges[Axis::Y].cleanup();
        HBridges[Axis::Z].cleanup();
    }
}

#else // fake magnetorquer

namespace Modules {
    void Magnetorquer::initialize() {
        // sike
    }

    void Magnetorquer::set_torque_direction(Axis axis, HBridgeDirection direction) {
        HBridgesDirections[axis] = direction;
    }

    void Magnetorquer::reset_torque_directions() {
        set_torque_direction(Axis::X, NONE);
        set_torque_direction(Axis::Y, NONE);
        set_torque_direction(Axis::Z, NONE);
    }

    void Magnetorquer::cleanup() {
        // sike
    }
}

#endif // RASPBERRY_PI