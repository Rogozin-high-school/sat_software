#pragma once

struct Satellite
{
    static void initialize();
    static void run();
    static void cleanup() noexcept;
};