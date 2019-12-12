#include <satellite.hpp>
#include <logger.hpp>

Satellite satellite;

int main(void)
{
    int err = satellite.initialize();
    if (err)
    {
        log << "satellite.initialize() has failed!\n";
        return err;
    }

    err = satellite.run();
    if (err)
    {
        log << "satellite.run() has failed!\n";
        satellite.cleanup();
        return err;
    }
}

int Satellite::initialize() noexcept
{
    return 0;
}

int Satellite::run() noexcept
{
    return 0;
}

void Satellite::cleanup() noexcept
{
}