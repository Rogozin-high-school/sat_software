#pragma once

class Satellite
{
public:
    static int initialize() noexcept;
    static int run() noexcept;
    static void cleanup() noexcept;
};