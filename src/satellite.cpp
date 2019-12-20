#include <satellite.hpp>
#include <properties.hpp>
#include <iostream>

int main(void)
{
    try 
    {
        Satellite::initialize();
        Satellite::run();
    }
    catch (const std::string& err)
    {
        log("%s\n", err.c_str());
    }

    Satellite::cleanup();
}

inline void Satellite::initialize()
{
    log("Called Satellite::initialize()\n");

    try
    {
        Properties::load();
        // TODO: Initialize sub-systems
    }
    catch (const std::string& err)
    {
        log("%s\n", err.c_str());
        throw std::string("Error: Satellite::initialize() has failed!");
    }
}

inline void Satellite::run()
{
    log("Called Satellite::run()\n");

    try
    {
        // TODO: Run
    }
    catch (const std::string& err)
    {
        log("%s\n", err.c_str());
        throw std::string("Error: Satellite::run() has failed!");
    }
}

inline void Satellite::cleanup() noexcept
{
    log("Called Satellite::cleanup()\n");
}