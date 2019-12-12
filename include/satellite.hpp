#pragma once

class Satellite
{
public:
    int initialize() noexcept;
    int run() noexcept;
    void cleanup() noexcept;
};

extern Satellite satellite;