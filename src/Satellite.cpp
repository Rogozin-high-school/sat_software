#include <Satellite.hpp>
#include <Properties.hpp>
#include <Components.hpp>
#include <SubSystems.hpp>
#include <SubSystems/Communication.hpp>

#include <unistd.h>

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
        Components::initialize();
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

    using Communication = SubSystems::Communication;
    using Command = Communication::Command;

    try
    {
        Communication::run();

        while (Communication::command != Command::Terminate)
        {
            Satellite::update();
            usleep(1000000 / refreshRateHz);
        }
    }
    catch (const std::exception &ex)
    {
        log_catch_and_throw_exception();
        throw ex;
    }
}

void Satellite::update()
{
    
}

void Satellite::cleanup() noexcept
{
    log_function_call();

    SubSystems::cleanup();
    Components::cleanup();
}