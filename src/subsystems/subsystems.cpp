#include <subsystems.hpp>
#include <stdexcept>

void Subsystems::initialize()
{
    log("Called Subsystems::initialize()\n");

    try
    {
        // TODO: Initialize sub-systems
    }
    catch (const std::runtime_error& err)
    {
        log("Error in Subsystems::initialize(): %s\n", err.what());
        throw std::runtime_error("Subsystems::initialize() has failed!");
    }
}