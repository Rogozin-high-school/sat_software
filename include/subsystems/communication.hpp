#pragma once

namespace SubSystems
{
struct Communication
{
    static void initialize();
    static void cleanup() noexcept;
};
} // namespace SubSystems