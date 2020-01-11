#include <subsystems.hpp>
#include <subsystems/communication.hpp>
#include <subsystems/telemetry.hpp>
#include <logger.hpp>

void SubSystems::initialize()
{
    log_function_call();

    try
    {
        Communication::initialize();
        Telemetry::initialize();
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
    Telemetry::cleanup();
}