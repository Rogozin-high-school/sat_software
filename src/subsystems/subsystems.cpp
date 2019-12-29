#include <subsystems.hpp>
#include <logger.hpp>

void SubSystems::initialize()
{
    print_function_call();

    try
    {
        // TODO: Initialize sub-systems
    }
    catch (const std::exception &ex)
    {
        print_catch_and_throw_exception();
        throw ex;
    }
}

void SubSystems::cleanup() noexcept
{
    print_function_call();
}