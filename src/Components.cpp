#include <Components.hpp>
#include <Components/IMU.hpp>

void Components::initialize()
{
    log_function_call();

    try
    {
        IMU::initialize();
    }
    catch (const std::exception &ex)
    {
        log_catch_and_throw_exception();
        throw ex;
    }
}

void Components::cleanup() noexcept
{
    log_function_call();

    IMU::cleanup();
}