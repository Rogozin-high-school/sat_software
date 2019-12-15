#pragma once

struct Satellite
{
    static bool initialize() noexcept;
    static void run() noexcept;
    static void cleanup() noexcept;
};