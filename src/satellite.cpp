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
        print_catch_and_handle_exception();
    }

    Satellite::cleanup();
}

inline void Satellite::initialize()
{
    print_function_call();

    try
    {
        Properties::load();
        SubSystems::initialize();
    }
    catch (const std::exception& ex)
    {
        print_catch_and_throw_exception();
        throw ex;
    }
}

inline void Satellite::run()
{
    print_function_call();

    try
    {
        // TODO: Run
    }
    catch (const std::exception& ex)
    {
        print_catch_and_throw_exception();
        throw ex;
    }
}

inline void Satellite::cleanup() noexcept
{
    print_function_call();

    SubSystems::cleanup();
}