#include <subsystems.hpp>
#include <stdexcept>

void SubSystems::initialize()
{
    log("Called SubSystems::initialize()\n");

    try
    {
        // TODO: Initialize sub-systems
    }
    catch (const std::runtime_error& err)
    {
        log("Error in SubSystems::initialize(): %s\n", err.what());
        throw std::runtime_error("SubSystems::initialize() has failed!");
    }
}

void SubSystems::cleanup() noexcept
{
    log("Called SubSystems::cleanup()\n");
}