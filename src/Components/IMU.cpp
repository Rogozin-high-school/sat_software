#include <Components/IMU.hpp>

void Components::IMU::initialize()
{
    log_function_call();

    try
    {
        // TODO
    }
    catch (const std::exception &ex)
    {
        log_catch_and_throw_exception();
        throw ex;
    }
}

void Components::IMU::cleanup() noexcept
{
    log_function_call();

    // TODO
}