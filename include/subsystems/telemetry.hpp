#pragma once

namespace SubSystems
{
struct Telemetry
{
    static void initialize();
    static void cleanup() noexcept;
};
} // namespace SubSystems