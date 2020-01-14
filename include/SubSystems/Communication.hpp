#pragma once

namespace SubSystems
{
struct Communication
{
    static enum class Command : uint8_t
    {
        None = 0x00,
        Terminate = 0xff
    } command;

    static void initialize();
    static void run() noexcept;
    static void cleanup() noexcept;
};
} // namespace SubSystems