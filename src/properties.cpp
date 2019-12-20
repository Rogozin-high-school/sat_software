#include <properties.hpp>
#include <map>
#include <fstream>
#include <sstream>

std::map<std::string, std::string> properties;

void Properties::load(std::string&& fileName)
{
    log << "Called Properties::load() with fileName = \"" << fileName << "\"" << std::endl;

    std::ifstream file(fileName);
    if (!file)
    {
        throw std::runtime_error("Can't open properties file: \"" + std::string(fileName) + "\"!");
    }

    std::string line, key, value;
    while (std::getline(file, line))
    {
        std::stringstream stream(std::move(line));
        std::getline(stream, key, ' ');
        std::getline(stream, value, ' ');
        properties[key] = value;

        log << "Loaded property: " << key << " = " << value << std::endl;
    }

    file.close();
}

const std::string_view Properties::get_string(std::string&& key)
{
    log << "Called Properties::get_string() with key = \"" << key << "\"" << std::endl;
    if (properties.empty())
    {
        throw std::runtime_error("Properties are yet to be loaded!");
    }
    const std::string& raw = properties[key];
    return raw.substr(1, raw.length() - 2);
}

int Properties::get_int(std::string&& key)
{
    log << "Called Properties::get_int() with key = \"" << key << "\"" << std::endl;
    if (properties.empty())
    {
        throw std::runtime_error("Properties are yet to be loaded!");
    }
    return stoi(properties[key]);
}