#include <satellite.hpp>
#include <client.hpp>
#include <logger.hpp>

int main(void)
{
    int err = Satellite::initialize();
    if (err)
    {
        log << "satellite.initialize() has failed with code " << err << "!\n";
        return err;
    }

    err = Satellite::run();
    if (err)
    {
        log << "satellite.run() has failed with code " << err << "!\n";
        Satellite::cleanup();
        return err;
    }
}

inline int Satellite::initialize() noexcept
{
    // TODO: Load properties
    int err = Client::initialize();
    if (err)
    {
        log << "client.initialize() has failed with code " << err << "!\n";
        return err;
    }
    // TODO: Initialize modules
    return 0;
}

inline int Satellite::run() noexcept
{
    int err = Client::run();
    if (err)
    {
        log << "client.run() has failed with code " << err << "!\n";
        return err;
    }
    return 0;
}

inline void Satellite::cleanup() noexcept
{
}