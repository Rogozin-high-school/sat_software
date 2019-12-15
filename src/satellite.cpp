#include <satellite.hpp>
#include <client.hpp>
#include <logger.hpp>

int main(void)
{
    if (!Satellite::initialize())
    {
        log("satellite.initialize() has failed!\n");
        return 1;
    }
    Satellite::run();
    Satellite::cleanup();
}

inline bool Satellite::initialize() noexcept
{
    // TODO: Load properties
    if (!Client::initialize())
    {
        log("client.initialize() has failed!\n");
        return false;
    }
    // TODO: Initialize modules
    return true;
}

inline void Satellite::run() noexcept
{
    Client::run();
}

inline void Satellite::cleanup() noexcept
{
}