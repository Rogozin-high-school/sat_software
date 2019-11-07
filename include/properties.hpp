#pragma once

#include <string>
#include <map>

class Properties {
    static constexpr auto fileName = "properties";
public:
    static void reload();

    static const std::string& raw_get(std::string propertyName);
    
    static std::string get_string(std::string propertyName);

    static int get_int(std::string propertyName);

    static std::pair<uint8_t, uint8_t> get_byte_pair(std::string propertyName);
private:
    static std::map<std::string, std::string> properties;
};