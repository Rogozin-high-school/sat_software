#include <properties.hpp>
#include <map>
#include <fstream>
#include <sstream>

std::map<std::string, std::string> properties;

bool Properties::load() noexcept
{
    constexpr auto fileName = "properties";

    std::ifstream file(fileName);
    if (!file)
    {
        log("[Properties] Can't open file: \"%s\"\n", fileName);
        return false;
    }

    std::string line, key, value;
    while (std::getline(file, line))
    {
        std::stringstream stream(std::move(line));
        std::getline(stream, key, ' ');
        std::getline(stream, value, ' ');
        properties[key] = value;

        log("[Properties] Loaded: %s => %s\n", key.c_str(), value.c_str());
    }

    file.close();
    return true;
}

optional_string Properties::get_string(std::string&& property) noexcept
{
    if (properties.count(property)) 
    { // If exists in the map
        const std::string& raw = properties[property];
        return raw.substr(1, raw.length() - 2);
    }
    return {};
}

optional_int Properties::get_int(std::string&& property) noexcept
{
    if (properties.count(property))
    { // If exists in the map
        return stoi(properties[property]);
    }
    return {};
}