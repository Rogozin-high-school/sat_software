#include <properties.hpp>
#include <map>
#include <fstream>
#include <sstream>

std::map<std::string, std::string> properties;

void Properties::load(std::string&& fileName)
{
    log("Called Properties::load() with fileName = \"%s\"\n", fileName.c_str());

    std::ifstream file(fileName);
    if (!file)
    {
        throw std::string("Error: Can't open properties file: \"" + std::string(fileName) + "\"!");
    }

    std::string line, key, value;
    while (std::getline(file, line))
    {
        std::stringstream stream(std::move(line));
        std::getline(stream, key, ' ');
        std::getline(stream, value, ' ');
        properties[key] = value;

        log("Loaded property: %s = %s\n", key.c_str(), value.c_str());
    }

    file.close();
}

const std::string_view Properties::get_string(std::string&& key)
{
    log("Called Properties::get_string() with key = \"%s\"\n", key.c_str());
    if (properties.empty())
    {
        throw std::string("Error: Properties are yet to be loaded!");
    }
    const std::string& raw = properties[key];
    return raw.substr(1, raw.length() - 2);
}

int Properties::get_int(std::string&& key)
{
    log("Called Properties::get_int() with key = \"%s\"\n", key.c_str());
    if (properties.empty())
    {
        throw std::string("Error: Properties are yet to be loaded!");
    }
    return stoi(properties[key]);
}