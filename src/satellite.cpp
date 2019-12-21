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
    catch (const std::exception&)
    {
        failure();
    }

    Satellite::cleanup();
}

inline void Satellite::initialize()
{
    function_call();

    try
    {
        Properties::load();
        SubSystems::initialize();
    }
    catch (const std::exception& ex)
    {
        failure();
        throw ex;
    }
}

inline void Satellite::run()
{
    function_call();

    try
    {
        // TODO: Run
        Properties::get_string("tick_delay_micros");
    }
    catch (const std::exception& ex)
    {
        failure();
        throw ex;
    }
}

inline void Satellite::cleanup() noexcept
{
    function_call();

    SubSystems::cleanup();
}