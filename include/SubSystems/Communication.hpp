#pragma once

namespace SubSystems
{
struct Communication
{
    static void initialize();
    static void run() noexcept;
    static void cleanup() noexcept;
};
} // namespace SubSystems