#pragma once

#include <modules/module_base.hpp>
#include <modules/magnetorquer/hbridge.hpp>

namespace Modules {
    class Magnetorquer {
    public:
        void initialize();
        void set_torque_direction(Axis axis, SubModules::HBridge::Direction direction);
        void reset_torque_directions();
        void cleanup();
    private:
        std::unordered_map<Axis, SubModules::HBridge> HBridges;
    };
}
