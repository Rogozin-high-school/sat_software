#include <satellite.hpp>
#include <properties.hpp>
#include <subsystems.hpp>
#include <subsystems/communication.hpp>
#include <logger.hpp>

int main()
{
    try
    {
        Satellite::initialize();
        Satellite::run();
    }
    catch (const std::exception &)
    {
        log_catch_and_handle_exception();
    }
    Satellite::cleanup();
}

void Satellite::initialize()
{
    log_function_call();

    try
    {
        Properties::load();
        SubSystems::initialize();
    }
    catch (const std::exception &ex)
    {
        log_catch_and_throw_exception();
        throw ex;
    }
}

void Satellite::run()
{
    log_function_call();

    try
    {
        Properties::get_int("hello");
        SubSystems::Communication::run();
    }
    catch (const std::exception &ex)
    {
        log_catch_and_throw_exception();
        throw ex;
    }
}

void Satellite::cleanup() noexcept
{
    log_function_call();

    SubSystems::cleanup();
}