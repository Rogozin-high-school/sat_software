#include <satellite.hpp>
#include <properties.hpp>
#include <subsystems.hpp>

int main(void)
{
    try 
    {
        Satellite::initialize();
        Satellite::run();
    }
    catch (const std::runtime_error& err)
    {
        log << "Error in main(): " << err.what() << std::endl;
    }

    Satellite::cleanup();
}

inline void Satellite::initialize()
{
    log << "Called Satellite::initialize()" << std::endl;

    try
    {
        Properties::load();
        SubSystems::initialize();
    }
    catch (const std::runtime_error& err)
    {
        log << "Error in Satellite::initialize(): " << err.what() << std::endl;
        throw std::runtime_error("Satellite::initialize() has failed!");
    }
}

inline void Satellite::run()
{
    log << "Called Satellite::run()" << std::endl;

    try
    {
        // TODO: Run
    }
    catch (const std::runtime_error& err)
    {
        log << "Error in Satellite::run(): " << err.what() << std::endl;
        throw std::runtime_error("Satellite::run() has failed!");
    }
}

inline void Satellite::cleanup() noexcept
{
    log << "Called Satellite::cleanup()" << std::endl;
    SubSystems::cleanup();
}