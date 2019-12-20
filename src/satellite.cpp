#include <satellite.hpp>
#include <properties.hpp>
#include <subsystems.hpp>
#include <stdexcept>

int main(void)
{
    try 
    {
        Satellite::initialize();
        Satellite::run();
    }
    catch (const std::runtime_error& err)
    {
        log("Error in main(): %s\n", err.what());
    }

    Satellite::cleanup();
}

inline void Satellite::initialize()
{
    log("Called Satellite::initialize()\n");

    try
    {
        Properties::load();
        Subsystems::initialize();
    }
    catch (const std::runtime_error& err)
    {
        log("Error in Satellite::initialize(): %s\n", err.what());
        throw std::runtime_error("Satellite::initialize() has failed!");
    }
}

inline void Satellite::run()
{
    log("Called Satellite::run()\n");

    try
    {
        // TODO: Run
    }
    catch (const std::runtime_error& err)
    {
        log("Error in Satellite::run(): %s\n", err.what());
        throw std::runtime_error("Satellite::run() has failed!");
    }
}

inline void Satellite::cleanup() noexcept
{
    log("Called Satellite::cleanup()\n");
}