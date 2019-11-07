#include <modules/magnetorquer/magnetorquer.hpp>
#include <logger.hpp>
#include <properties.hpp>

namespace Modules {
    void Magnetorquer::initialize() {
        Logger::verbose<LogPrefix::MAGNETORQUER>("Initializing...");

        {
            auto[pin1, pin2] = Properties::get_byte_pair("Hbridge_axis_x_pins");
            Hbridges[Axis::X].initialize(GPIO::Pin(pin1), GPIO::Pin(pin2));

            Logger::verbose<LogPrefix::HBRIDGE>("Initialized X axis!");
        }

        {
            auto[pin1, pin2] = Properties::get_byte_pair("Hbridge_axis_y_pins");
            Hbridges[Axis::Y].initialize(GPIO::Pin(pin1), GPIO::Pin(pin2));

            Logger::verbose<LogPrefix::HBRIDGE>("Initialized Y axis!");
        }

        {
            auto[pin1, pin2] = Properties::get_byte_pair("Hbridge_axis_z_pins");
            Hbridges[Axis::Z].initialize(GPIO::Pin(pin1), GPIO::Pin(pin2));

            Logger::verbose<LogPrefix::HBRIDGE>("Initialized Z axis!");
        }

        Logger::debug<LogPrefix::MAGNETORQUER>("Ready!");
    }

    void Magnetorquer::set_torque_direction(Axis axis, HBridge::Direction direction) {
        std::string axisStr = "X";
        if (axis == Axis::Y) {
            axisStr = "Y";
        } else if (axis == Axis::Z) {
            axisStr = "Z";
        }

        std::string directionStr = "none";
        if (direction == HBridge::Direction::FORWARD) {
            directionStr = "forward";
        } else if (direction == HBridge::Direction::BACKWARD) {
            directionStr = "backward";
        }

        Logger::verbose<LogPrefix::MAGNETORQUER>("Setting torque direction to " + directionStr + " on the " + axisStr + " axis!");
        Hbridges[axis].set_direction(direction);
    }

    void Magnetorquer::reset_torque_directions() {
        Logger::verbose<LogPrefix::MAGNETORQUER>("Resetting torque directions!");
        set_torque_direction(Axis::X, HBridge::Direction::NONE);
        set_torque_direction(Axis::Y, HBridge::Direction::NONE);
        set_torque_direction(Axis::Z, HBridge::Direction::NONE);
    }

    void Magnetorquer::cleanup() {
        Logger::verbose<LogPrefix::MAGNETORQUER>("Cleaning up!");
        
        reset_torque_directions();

        Logger::verbose<LogPrefix::HBRIDGE>("Cleaning up X axis!");
        Hbridges[Axis::X].cleanup();

        Logger::verbose<LogPrefix::HBRIDGE>("Cleaning up Y axis!");
        Hbridges[Axis::Y].cleanup();

        Logger::verbose<LogPrefix::HBRIDGE>("Cleaning up Z axis!");
        Hbridges[Axis::Z].cleanup();

        Logger::verbose<LogPrefix::MAGNETORQUER>("All cleaned up!");
    }
}