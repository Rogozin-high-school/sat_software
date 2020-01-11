#include <subsystems/telemetry.hpp>
#include <logger.hpp>

void SubSystems::Telemetry::initialize()
{
    log_function_call();
}

void SubSystems::Telemetry::cleanup() noexcept
{
    log_function_call();
}
