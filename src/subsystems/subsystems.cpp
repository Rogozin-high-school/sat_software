#include <subsystems.hpp>

void SubSystems::initialize()
{
    log << "Called SubSystems::initialize()" << std::endl;

    try
    {
        // TODO: Initialize sub-systems
    }
    catch (const std::runtime_error& err)
    {
        log << "Error in SubSystems::initialize(): " << err.what() << std::endl;
        throw std::runtime_error("SubSystems::initialize() has failed!");
    }
}

void SubSystems::cleanup() noexcept
{
    log << "Called SubSystems::cleanup()" << std::endl;
}