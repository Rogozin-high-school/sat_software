#include <subsystems.hpp>
#include <subsystems/communication.hpp>
#include <logger.hpp>

void SubSystems::initialize()
{
    print_function_call();

    try
    {
        Communication::initialize();
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

    Communication::cleanup();
}