#pragma once

struct Properties
{
    static void load(std::string&& fileName = "properties");
    static const std::string_view get_string(std::string&& key); 
    static int get_int(std::string&& key); 
};