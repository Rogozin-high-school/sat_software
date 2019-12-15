#include <properties.hpp>
#include <logger.hpp>
#include <map>
#include <fstream>
#include <sstream>

constexpr auto fileName = "properties";

std::map<std::string, std::string> properties;

bool Properties::load() noexcept
{
    std::ifstream file(fileName);
    if (!file)
    {
        log("Can't open properties file: \"%s\"\n", fileName);
        return false;
    }

    std::string line, key, value;

    while (std::getline(file, line))
    {
        std::stringstream stream(std::move(line));
        std::getline(stream, key, ' ');
        std::getline(stream, value, ' ');
        properties[key] = value;
    }

    file.close();
    return true;
}

std::string Properties::get_string(std::string&& property) noexcept
{
    const std::string& raw = properties[property];
    return raw.substr(1, raw.length() - 2);
}

int Properties::get_int(std::string&& property) noexcept
{
    return stoi(properties[property]);
}