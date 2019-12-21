#include <subsystems.hpp>

void SubSystems::initialize()
{
    print_function_call();

    try
    {
        // TODO: Initialize sub-systems
    }
    catch (const std::exception& ex)
    {
        print_failure();
        throw ex;
    }
}

void SubSystems::cleanup() noexcept
{
    print_function_call();
}