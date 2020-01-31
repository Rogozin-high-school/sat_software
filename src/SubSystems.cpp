#include <SubSystems.hpp>
#include <SubSystems/Communication.hpp>

void SubSystems::initialize()
{
    log_function_call();

    try
    {
        Communication::initialize();
    }
    catch (const std::exception &ex)
    {
        log_catch_and_throw_exception();
        throw ex;
    }
}

void SubSystems::cleanup() noexcept
{
    log_function_call();

    Communication::cleanup();
}