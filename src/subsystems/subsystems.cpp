#include <subsystems.hpp>

void SubSystems::initialize()
{
    function_call();

    try
    {
        // TODO: Initialize sub-systems
    }
    catch (const std::exception& ex)
    {
        failure();
        throw ex;
    }
}

void SubSystems::cleanup() noexcept
{
    function_call();
}