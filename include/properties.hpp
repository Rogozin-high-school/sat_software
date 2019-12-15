#pragma once

#include <string>

struct Properties
{
    static bool load() noexcept;
    static std::string get_string(std::string&& property) noexcept; 
    static int get_int(std::string&& property) noexcept; 
};