#pragma once

struct Satellite
{
    static constexpr uint32_t refreshRateHz = 20; // updates/sec

    static void initialize();
    static void run();
    static void update();
    static void cleanup() noexcept;
};
