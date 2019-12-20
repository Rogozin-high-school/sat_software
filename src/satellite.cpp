#include <satellite.hpp>
#include <properties.hpp>

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
    if (!Properties::load())
    {
        log("properties.load() has failed!\n");
        return false;
    }
    
    // TODO: Initialize sub-systems
    
    return false;
}

inline void Satellite::run() noexcept
{
}

inline void Satellite::cleanup() noexcept
{
}