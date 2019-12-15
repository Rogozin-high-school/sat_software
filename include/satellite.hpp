#pragma once

struct Satellite
{
    static bool initialize() noexcept;
    static bool run() noexcept;
    static void cleanup() noexcept;
};