#pragma once

#include <string>

struct Properties
{
    static void load(std::string &&fileName = PROPERTIES_FILE);
    static const std::string_view get_string(std::string &&key);
    static int get_int(std::string &&key);
};